#ifndef GB_MMU_H
#define GB_MMU_H

typedef struct gb_mmu_s {
    unsigned char memory[0x10000]; // 64KB memory
} gb_mmu_t;

void gb_mmu_reset(gb_mmu_t *mmu);

#endif // GB_MMU_H
