#include "mmu.h"
#include <string.h>

// Initialize all MMU memory regions
void gb_mmu_reset(gb_mmu_t *mmu) {
    if (!mmu) return;

    memset(mmu->rom, 0, ROM_SIZE_MAX);
    memset(mmu->vram, 0, VRAM_SIZE);
    memset(mmu->eram, 0, EXTRAM_SIZE);
    memset(mmu->wram, 0, WRAM_SIZE);
    memset(mmu->oam, 0, OAM_SIZE);
    memset(mmu->io, 0, IO_SIZE);
    memset(mmu->hram, 0, HRAM_SIZE);
    mmu->ie = 0;
}

// Read a byte from the MMU
uint8_t gb_mmu_read_byte(gb_mmu_t *mmu, uint16_t addr) {
    if (!mmu) return 0xFF;

    if (addr <= 0x7FFF) {              // ROM
        return mmu->rom[addr];
    } else if (addr >= 0x8000 && addr <= 0x9FFF) { // VRAM
        return mmu->vram[addr - 0x8000];
    } else if (addr >= 0xA000 && addr <= 0xBFFF) { // External RAM
        return mmu->eram[addr - 0xA000];
    } else if (addr >= 0xC000 && addr <= 0xDFFF) { // Work RAM
        return mmu->wram[addr - 0xC000];
    } else if (addr >= 0xE000 && addr <= 0xFDFF) { // Echo RAM
        return mmu->wram[addr - 0xE000];
    } else if (addr >= 0xFE00 && addr <= 0xFE9F) { // OAM
        return mmu->oam[addr - 0xFE00];
    } else if (addr >= 0xFF00 && addr <= 0xFF7F) { // I/O registers
        return mmu->io[addr - 0xFF00];
    } else if (addr >= 0xFF80 && addr <= 0xFFFE) { // High RAM
        return mmu->hram[addr - 0xFF80];
    } else if (addr == 0xFFFF) {       // Interrupt Enable register
        return mmu->ie;
    }

    return 0xFF; // Default fallback
}

// Write a byte to the MMU
void gb_mmu_write_byte(gb_mmu_t *mmu, uint16_t addr, uint8_t val) {
    if (!mmu) return;

    if (addr <= 0x7FFF) {              // ROM is read-only
        return;
    } else if (addr >= 0x8000 && addr <= 0x9FFF) { // VRAM
        mmu->vram[addr - 0x8000] = val;
    } else if (addr >= 0xA000 && addr <= 0xBFFF) { // External RAM
        mmu->eram[addr - 0xA000] = val;
    } else if (addr >= 0xC000 && addr <= 0xDFFF) { // Work RAM
        mmu->wram[addr - 0xC000] = val;
    } else if (addr >= 0xE000 && addr <= 0xFDFF) { // Echo RAM
        mmu->wram[addr - 0xE000] = val;
    } else if (addr >= 0xFE00 && addr <= 0xFE9F) { // OAM
        mmu->oam[addr - 0xFE00] = val;
    } else if (addr >= 0xFF00 && addr <= 0xFF7F) { // I/O registers
        mmu->io[addr - 0xFF00] = val;
    } else if (addr >= 0xFF80 && addr <= 0xFFFE) { // High RAM
        mmu->hram[addr - 0xFF80] = val;
    } else if (addr == 0xFFFF) {       // Interrupt Enable register
        mmu->ie = val;
    }
}

// Read a 16-bit word from memory
uint16_t gb_mmu_read_word(gb_mmu_t *mmu, uint16_t addr) {
    uint8_t lo = gb_mmu_read_byte(mmu, addr);
    uint8_t hi = gb_mmu_read_byte(mmu, addr + 1);
    return (hi << 8) | lo;
}

// Write a 16-bit word to memory
void gb_mmu_write_word(gb_mmu_t *mmu, uint16_t addr, uint16_t val) {
    gb_mmu_write_byte(mmu, addr, val & 0xFF);
    gb_mmu_write_byte(mmu, addr + 1, (val >> 8) & 0xFF);
}
