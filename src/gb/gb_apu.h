#ifndef GB_APU_H
#define GB_APU_H

#include <stdint.h>
#include <stdbool.h>

// Simple Game Boy APU (Audio Processing Unit) state
typedef struct {
    bool enabled;          // Whether the APU is active
    int sample_rate;       // Sample output rate (Hz)
    uint32_t cycles;       // Internal cycle counter
} gb_apu_t;

// Initialize or reset APU
void gb_apu_init(gb_apu_t *apu);
void gb_apu_reset(gb_apu_t *apu);

// Run APU for one tick (called every CPU cycle)
void gb_apu_tick(gb_apu_t *apu);

// Step APU by a number of cycles (used by CPU)
void gb_apu_step(gb_apu_t *apu, int cycles);

#endif // GB_APU_H
