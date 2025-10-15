#ifndef GBA_CPU_H
#define GBA_CPU_H

#include <stdint.h>
#include "gba_mmu.h"

typedef struct {
    uint32_t regs[16]; // R0-R15
    uint32_t cpsr;     // Current Program Status Register
    gba_mmu_t *mmu;    // Pointer to MMU
} gba_cpu_t;

void gba_cpu_init(gba_cpu_t *cpu, gba_mmu_t *mmu);
void gba_cpu_reset(gba_cpu_t *cpu);
void gba_cpu_step(gba_cpu_t *cpu);

#endif // GBA_CPU_H
