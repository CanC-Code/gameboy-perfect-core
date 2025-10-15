#ifndef MMU_H
#define MMU_H

#include <stdint.h>

/* Minimal MMU struct */
typedef struct {
    uint8_t memory[0x10000]; /* 64KB memory */
} gb_mmu_t;

#endif
