#include "mmu.h"
#include <string.h>

bool gba_mmu_init(gba_mmu_t *mmu, uint8_t *bios, uint8_t *rom, uint32_t rom_size) {
    if (!mmu || !bios || !rom || rom_size == 0) return false;

    mmu->bios = bios;
    mmu->rom = rom;
    mmu->rom_size = rom_size;

    memset(mmu->wram, 0, sizeof(mmu->wram));
    memset(mmu->ewram, 0, sizeof(mmu->ewram));
    memset(mmu->io_regs, 0, sizeof(mmu->io_regs));

    return true;
}

void gba_mmu_reset(gba_mmu_t *mmu) {
    if (!mmu) return;
    memset(mmu->wram, 0, sizeof(mmu->wram));
    memset(mmu->ewram, 0, sizeof(mmu->ewram));
    memset(mmu->io_regs, 0, sizeof(mmu->io_regs));
}

uint8_t gba_mmu_read8(gba_mmu_t *mmu, uint32_t addr) {
    if (!mmu) return 0xFF;

    if (addr < 0x400000) return mmu->bios[addr];        // BIOS
    if (addr >= 0x2000000 && addr < 0x2000000 + GBA_RAM_SIZE) return mmu->wram[addr - 0x2000000];
    if (addr >= 0x3000000 && addr < 0x3000000 + GBA_EWRAM_SIZE) return mmu->ewram[addr - 0x3000000];
    if (addr >= 0x4000000 && addr < 0x4000000 + GBA_IO_SIZE) return mmu->io_regs[addr - 0x4000000];
    if (addr >= 0x8000000 && addr < 0x8000000 + mmu->rom_size) return mmu->rom[addr - 0x8000000];

    return 0xFF; // unmapped
}

uint16_t gba_mmu_read16(gba_mmu_t *mmu, uint32_t addr) {
    uint8_t lo = gba_mmu_read8(mmu, addr);
    uint8_t hi = gba_mmu_read8(mmu, addr + 1);
    return lo | (hi << 8);
}

uint32_t gba_mmu_read32(gba_mmu_t *mmu, uint32_t addr) {
    uint16_t lo = gba_mmu_read16(mmu, addr);
    uint16_t hi = gba_mmu_read16(mmu, addr + 2);
    return lo | (hi << 16);
}

void gba_mmu_write8(gba_mmu_t *mmu, uint32_t addr, uint8_t value) {
    if (!mmu) return;

    if (addr >= 0x2000000 && addr < 0x2000000 + GBA_RAM_SIZE) mmu->wram[addr - 0x2000000] = value;
    else if (addr >= 0x3000000 && addr < 0x3000000 + GBA_EWRAM_SIZE) mmu->ewram[addr - 0x3000000] = value;
    else if (addr >= 0x4000000 && addr < 0x4000000 + GBA_IO_SIZE) mmu->io_regs[addr - 0x4000000] = value;
}

void gba_mmu_write16(gba_mmu_t *mmu, uint32_t addr, uint16_t value) {
    gba_mmu_write8(mmu, addr, value & 0xFF);
    gba_mmu_write8(mmu, addr + 1, value >> 8);
}

void gba_mmu_write32(gba_mmu_t *mmu, uint32_t addr, uint32_t value) {
    gba_mmu_write16(mmu, addr, value & 0xFFFF);
    gba_mmu_write16(mmu, addr + 2, value >> 16);
}
