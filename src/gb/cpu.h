#ifndef GB_CPU_H
#define GB_CPU_H

// Forward declaration to break circular dependency
typedef struct core_state_s core_state_t;

// CPU type
typedef struct gb_cpu_s {
    // Example registers
    unsigned char A, B, C, D, E, F, H, L;
    unsigned short SP, PC;
} gb_cpu_t;

// Functions
void gb_cpu_reset(gb_cpu_t *cpu);
void cpu_reset(core_state_t *state);
void cpu_step(core_state_t *state);

#endif // GB_CPU_H
