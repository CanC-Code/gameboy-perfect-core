#ifndef GBA_CPU_H
#define GBA_CPU_H

#include <stdint.h>
#include "gba_mmu.h"

typedef struct gba_cpu_t {
    uint32_t regs[16];       // R0-R15
    uint32_t cpsr;           // Current Program Status Register
    gba_mmu_t *mmu;          // pointer to MMU
} gba_cpu_t;

void gba_cpu_init(gba_cpu_t *cpu, gba_mmu_t *mmu);
uint32_t gba_cpu_fetch32(gba_cpu_t *cpu, uint32_t addr);
void gba_cpu_step(gba_cpu_t *cpu);  // execute one instruction (placeholder)

#endif // GBA_CPU_H
