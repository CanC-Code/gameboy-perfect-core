#include "gba_mmu.h"
#include <string.h>
#include <stdio.h>

void gba_mmu_init(gba_mmu_t *mmu) {
    gba_mmu_reset(mmu);
}

void gba_mmu_reset(gba_mmu_t *mmu) {
    memset(mmu->rom, 0, GBA_ROM_SIZE);
    memset(mmu->ram, 0, GBA_RAM_SIZE);
}

int gba_mmu_load_rom(gba_mmu_t *mmu, const void *data, size_t size) {
    if (size > GBA_ROM_SIZE) return -1;
    memcpy(mmu->rom, data, size);
    return 0;
}
