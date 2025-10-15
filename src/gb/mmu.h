#ifndef GB_MMU_H
#define GB_MMU_H

#include <stdint.h>

typedef struct {
    uint8_t memory[0x10000]; // 64KB Game Boy memory map
} gb_mmu_t;

void gb_mmu_reset(gb_mmu_t *mmu);
uint8_t gb_mmu_read_byte(gb_mmu_t *mmu, uint16_t addr);
void gb_mmu_write_byte(gb_mmu_t *mmu, uint16_t addr, uint8_t value);

#endif // GB_MMU_H
