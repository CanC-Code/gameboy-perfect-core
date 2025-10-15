#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdbool.h>

// Forward declare core_state_t so we can reference it
struct core_state_s;

typedef struct gb_cpu_s
{
    uint16_t pc;
    uint16_t sp;
    uint8_t a, f, b, c, d, e, h, l;
    bool halted;
} gb_cpu_t;

void gb_cpu_reset(gb_cpu_t *cpu);
void gb_cpu_step(gb_cpu_t *cpu, struct core_state_s *state);

#endif // CPU_H
