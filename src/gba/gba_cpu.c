#include "gba_cpu.h"
#include <string.h>

void gba_cpu_init(gba_cpu_t *cpu, uint8_t *memory) {
    cpu->memory = memory;
    memset(cpu->regs, 0, sizeof(cpu->regs));
    cpu->cpsr = 0;
}

void gba_cpu_reset(gba_cpu_t *cpu) {
    memset(cpu->regs, 0, sizeof(cpu->regs));
    cpu->cpsr = 0;
    cpu->regs[15] = 0x08000000; // typical entry for GBA ROM
}

void gba_cpu_step(gba_cpu_t *cpu, int cycles) {
    // Skeleton: Just increment PC
    for (int i = 0; i < cycles; i++) {
        cpu->regs[15] += 4; // move PC forward
    }
}
