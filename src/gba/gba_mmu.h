#ifndef GBA_MMU_H
#define GBA_MMU_H

#include <stdint.h>
#include <stddef.h>

#define GBA_MEM_SIZE 0x02000000 // 32MB address space

typedef struct {
    uint8_t mem[GBA_MEM_SIZE];
} gba_mmu_t;

// Initialize MMU
void gba_mmu_init(gba_mmu_t *mmu);

// Read/write helpers
uint8_t gba_mmu_read8(gba_mmu_t *mmu, uint32_t addr);
void gba_mmu_write8(gba_mmu_t *mmu, uint32_t addr, uint8_t value);

#endif // GBA_MMU_H
