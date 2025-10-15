#ifndef CPU_H
#define CPU_H

#include <stdint.h>

/* CPU struct */
typedef struct gb_cpu_s {
    uint16_t af, bc, de, hl;
    uint16_t sp;
    uint16_t pc;
} gb_cpu_t;

/* CPU step function */
struct core_state_s;
void gb_cpu_step(struct core_state_s *state);

#endif /* CPU_H */
