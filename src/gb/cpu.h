#ifndef GB_CPU_H
#define GB_CPU_H

#include <stdint.h>
#include <stdbool.h>

// Forward declaration so struct name is known
typedef struct core_state_s core_state_t;

// CPU register structure
typedef struct {
    union {
        struct { uint8_t f; uint8_t a; };
        uint16_t af;
    };
    union {
        struct { uint8_t c; uint8_t b; };
        uint16_t bc;
    };
    union {
        struct { uint8_t e; uint8_t d; };
        uint16_t de;
    };
    union {
        struct { uint8_t l; uint8_t h; };
        uint16_t hl;
    };
    uint16_t sp;
    uint16_t pc;
} gb_registers_t;

// CPU state structure
typedef struct {
    gb_registers_t reg;
    bool ime;
    bool halted;
} gb_cpu_t;

void gb_cpu_reset(gb_cpu_t *cpu);
void gb_cpu_step(core_state_t *state);

#endif // GB_CPU_H
