#include "gb_apu.h"
#include <string.h>
#include <stdbool.h>

void gb_apu_init(gb_apu_t *apu) {
    if (!apu) return;
    memset(apu, 0, sizeof(gb_apu_t));
    apu->sample_rate = 44100;
    apu->enabled = true;
    apu->cycles = 0;
}

void gb_apu_reset(gb_apu_t *apu) {
    if (!apu) return;
    apu->sample_rate = 44100;
    apu->enabled = true;
    apu->cycles = 0;
}

// Tick once per CPU cycle
void gb_apu_tick(gb_apu_t *apu) {
    if (!apu || !apu->enabled) return;
    apu->cycles++;
    // In future, generate samples or handle sound registers here.
}

// Advance by N CPU cycles
void gb_apu_step(gb_apu_t *apu, int cycles) {
    if (!apu || !apu->enabled) return;
    apu->cycles += cycles;
}
