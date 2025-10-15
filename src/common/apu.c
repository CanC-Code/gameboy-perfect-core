#include "apu.h"
#include <string.h>

// Reset the APU
void gb_apu_reset(gb_apu_t *apu) {
    if (!apu) return;
    memset(apu, 0, sizeof(gb_apu_t));
}

// Step the APU by a number of cycles
void gb_apu_step(gb_apu_t *apu, int cycles) {
    if (!apu) return;

    apu->cycle += cycles;

    while (apu->cycle >= 1) {
        // Here you would implement actual audio processing per cycle.
        // For now we just decrement the cycle counter.
        apu->cycle--;
    }
}
