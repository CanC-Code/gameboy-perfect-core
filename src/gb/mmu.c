#include "mmu.h"
#include <string.h>
#include <stdlib.h>

/* Game Boy memory regions */
#define ROM_BANK_SIZE 0x4000
#define VRAM_SIZE     0x2000
#define EXTRAM_SIZE   0x2000
#define WRAM_SIZE     0x2000
#define OAM_SIZE      0xA0
#define IO_SIZE       0x80
#define HRAM_SIZE     0x7F

typedef struct {
    /* ROM (cartridge, up to 32 MB for GBA, for now we allow up to 8MB) */
    uint8_t *rom;
    size_t rom_size;

    /* RAM banks (external cartridge RAM) */
    uint8_t eram[EXTRAM_SIZE];

    /* VRAM */
    uint8_t vram[VRAM_SIZE];

    /* Working RAM (WRAM) */
    uint8_t wram[WRAM_SIZE];

    /* Sprite Attribute Table (OAM) */
    uint8_t oam[OAM_SIZE];

    /* I/O registers */
    uint8_t io[IO_SIZE];

    /* High RAM (zero page) */
    uint8_t hram[HRAM_SIZE];

    /* MBC1 / MBC3 bank state (simplified) */
    uint8_t rom_bank; /* current ROM bank */
    uint8_t ram_bank; /* current RAM bank */
    bool ram_enable;

} gb_mmu_t;

/* Each core_state_t will carry a pointer to its MMU */
#define CORE_MMU(cs) ((gb_mmu_t *)(cs->fb_width)) // placeholder, will assign properly

/* Initialize MMU memory */
void gb_mmu_init(core_state_t *cs) {
    gb_mmu_t *mmu = (gb_mmu_t *)malloc(sizeof(gb_mmu_t));
    if (!mmu) return;
    memset(mmu, 0, sizeof(*mmu));
    cs->fb_width = (size_t)mmu; /* store MMU pointer temporarily */
}

/* Reset MMU to power-on state */
void gb_mmu_reset(core_state_t *cs) {
    gb_mmu_t *mmu = (gb_mmu_t *)cs->fb_width;
    if (!mmu) return;
    memset(mmu->vram, 0, sizeof(mmu->vram));
    memset(mmu->wram, 0, sizeof(mmu->wram));
    memset(mmu->oam, 0, sizeof(mmu->oam));
    memset(mmu->io, 0, sizeof(mmu->io));
    memset(mmu->hram, 0, sizeof(mmu->hram));
    mmu->rom_bank = 1;
    mmu->ram_bank = 0;
    mmu->ram_enable = false;
}

/* Load ROM into MMU */
bool gb_mmu_load_rom(core_state_t *cs, const void *data, size_t size) {
    gb_mmu_t *mmu = (gb_mmu_t *)cs->fb_width;
    if (!mmu || !data || size == 0) return false;

    mmu->rom = (uint8_t *)malloc(size);
    if (!mmu->rom) return false;

    memcpy(mmu->rom, data, size);
    mmu->rom_size = size;

    /* Reset banking state */
    mmu->rom_bank = 1;
    mmu->ram_bank = 0;
    mmu->ram_enable = false;
    return true;
}

/* Read a byte from memory */
uint8_t mmu_read8(core_state_t *cs, uint16_t addr) {
    gb_mmu_t *mmu = (gb_mmu_t *)cs->fb_width;
    if (!mmu) return 0xFF;

    if (addr < 0x4000) {
        return mmu->rom[addr];
    } else if (addr < 0x8000) {
        size_t offset = mmu->rom_bank * ROM_BANK_SIZE + (addr - 0x4000);
        if (offset >= mmu->rom_size) return 0xFF;
        return mmu->rom[offset];
    } else if (addr < 0xA000) {
        return mmu->vram[addr - 0x8000];
    } else if (addr < 0xC000) {
        return mmu->eram[addr - 0xA000];
    } else if (addr < 0xE000) {
        return mmu->wram[addr - 0xC000];
    } else if (addr < 0xFE00) {
        return mmu->wram[addr - 0xE000]; /* mirror */
    } else if (addr < 0xFEA0) {
        return mmu->oam[addr - 0xFE00];
    } else if (addr < 0xFF00) {
        return 0xFF; /* unusable */
    } else if (addr < 0xFF80) {
        return mmu->io[addr - 0xFF00];
    } else if (addr < 0xFFFF) {
        return mmu->hram[addr - 0xFF80];
    } else {
        return cs->ime; /* IE register at 0xFFFF */
    }
}

/* Write a byte to memory */
void mmu_write8(core_state_t *cs, uint16_t addr, uint8_t value) {
    gb_mmu_t *mmu = (gb_mmu_t *)cs->fb_width;
    if (!mmu) return;

    if (addr < 0x4000) {
        /* ROM bank 0 read-only */
    } else if (addr < 0x8000) {
        /* Switchable ROM bank (writes used for MBC control) */
        mmu->rom_bank = value & 0x7F;
        if (mmu->rom_bank == 0) mmu->rom_bank = 1;
    } else if (addr < 0xA000) {
        mmu->vram[addr - 0x8000] = value;
    } else if (addr < 0xC000) {
        if (mmu->ram_enable) mmu->eram[addr - 0xA000] = value;
    } else if (addr < 0xE000) {
        mmu->wram[addr - 0xC000] = value;
    } else if (addr < 0xFE00) {
        mmu->wram[addr - 0xE000] = value; /* mirror */
    } else if (addr < 0xFEA0) {
        mmu->oam[addr - 0xFE00] = value;
    } else if (addr < 0xFF00) {
        /* unusable memory, ignore */
    } else if (addr < 0xFF80) {
        mmu->io[addr - 0xFF00] = value;
    } else if (addr < 0xFFFF) {
        mmu->hram[addr - 0xFF80] = value;
    } else {
        cs->ime = value;
    }
}

/* Read 16-bit little-endian helper */
uint16_t mmu_read16(core_state_t *cs, uint16_t addr) {
    uint8_t lo = mmu_read8(cs, addr);
    uint8_t hi = mmu_read8(cs, addr + 1);
    return lo | (hi << 8);
}
