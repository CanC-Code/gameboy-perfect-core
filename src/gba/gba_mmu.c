#include "gba_mmu.h"
#include <string.h>

void gba_mmu_init(gba_mmu_t *mmu) {
    memset(mmu->mem, 0, sizeof(mmu->mem));
}

uint8_t gba_mmu_read8(gba_mmu_t *mmu, uint32_t addr) {
    return mmu->mem[addr % GBA_MEM_SIZE];
}

void gba_mmu_write8(gba_mmu_t *mmu, uint32_t addr, uint8_t value) {
    mmu->mem[addr % GBA_MEM_SIZE] = value;
}
