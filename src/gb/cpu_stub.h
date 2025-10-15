#ifndef GB_CPU_STUB_H
#define GB_CPU_STUB_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

struct gb_cpu_t {
    uint16_t pc;
    uint16_t sp;
    uint8_t  a, f, b, c, d, e, h, l;
    bool halted;
    uint64_t cycles;
};

// Initialize CPU state
void gb_cpu_init(struct gb_cpu_t *cpu);

// Execute one CPU cycle (stub)
void gb_cpu_step(struct gb_cpu_t *cpu);

#endif // GB_CPU_STUB_H
