#ifndef GBA_CPU_H
#define GBA_CPU_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
    uint32_t regs[16]; // R0-R15
    uint32_t cpsr;     // Current Program Status Register
    uint8_t *memory;   // pointer to MMU memory
} gba_cpu_t;

// Initialize CPU
void gba_cpu_init(gba_cpu_t *cpu, uint8_t *memory);

// Reset CPU
void gba_cpu_reset(gba_cpu_t *cpu);

// Execute N cycles
void gba_cpu_step(gba_cpu_t *cpu, int cycles);

#endif // GBA_CPU_H
