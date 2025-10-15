#ifndef GBA_MMU_H
#define GBA_MMU_H

#include <stdint.h>
#include <stdbool.h>
#include "cpu.h"
#include "core_common.h"

// Memory sizes
#define GBA_RAM_SIZE     0x40000     // 256KB internal working RAM
#define GBA_EWRAM_SIZE   0x40000     // External WRAM (256KB)
#define GBA_IO_SIZE      0x400       // IO registers

typedef struct {
    uint8_t wram[GBA_RAM_SIZE];
    uint8_t ewram[GBA_EWRAM_SIZE];
    uint8_t io_regs[GBA_IO_SIZE];
    uint8_t *bios;          // Pointer to 16KB BIOS
    uint8_t *rom;           // Pointer to cartridge ROM
    uint32_t rom_size;
} gba_mmu_t;

// MMU lifecycle
bool gba_mmu_init(gba_mmu_t *mmu, uint8_t *bios, uint8_t *rom, uint32_t rom_size);
void gba_mmu_reset(gba_mmu_t *mmu);

// Memory access
uint8_t  gba_mmu_read8(gba_mmu_t *mmu, uint32_t addr);
uint16_t gba_mmu_read16(gba_mmu_t *mmu, uint32_t addr);
uint32_t gba_mmu_read32(gba_mmu_t *mmu, uint32_t addr);

void gba_mmu_write8(gba_mmu_t *mmu, uint32_t addr, uint8_t value);
void gba_mmu_write16(gba_mmu_t *mmu, uint32_t addr, uint16_t value);
void gba_mmu_write32(gba_mmu_t *mmu, uint32_t addr, uint32_t value);

#endif // GBA_MMU_H
