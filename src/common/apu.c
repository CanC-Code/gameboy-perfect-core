#include "apu.h"
#include <math.h>
#include <string.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// --- Helpers for tone generation ---
static inline float square_wave(double phase) {
    return (fmod(phase, 1.0) < 0.5) ? 1.0f : -1.0f;
}

static inline float noise_sample(uint16_t *lfsr) {
    // 15-bit LFSR used in Game Boy noise channel
    uint16_t bit = (*lfsr ^ (*lfsr >> 1)) & 1;
    *lfsr = (*lfsr >> 1) | (bit << 14);
    return ((*lfsr & 1) ? 1.0f : -1.0f);
}

// --- Initialization ---
void gb_apu_init(gb_apu_t *apu) {
    memset(apu, 0, sizeof(gb_apu_t));
    apu->volume = 0.3f;
    apu->noise_lfsr = 0x7FFF;
    apu->cycles_per_sample = 4194304 / GB_APU_SAMPLE_RATE; // ~95 cycles/sample
}

// --- Reset ---
void gb_apu_reset(gb_apu_t *apu) {
    gb_apu_init(apu);
}

// --- Step the APU by CPU cycles ---
void gb_apu_step(gb_apu_t *apu, int cycles) {
    apu->cycle_counter += cycles;
    if (apu->cycle_counter < apu->cycles_per_sample)
        return;

    apu->cycle_counter -= apu->cycles_per_sample;

    // --- Generate simple tone for each channel ---
    float mix = 0.0f;

    if (apu->ch1_enabled) {
        apu->ch1_phase += 440.0 / GB_APU_SAMPLE_RATE;
        mix += square_wave(apu->ch1_phase);
    }

    if (apu->ch2_enabled) {
        apu->ch2_phase += 660.0 / GB_APU_SAMPLE_RATE;
        mix += square_wave(apu->ch2_phase);
    }

    if (apu->ch3_enabled) {
        apu->ch3_phase += 880.0 / GB_APU_SAMPLE_RATE;
        mix += sinf(2.0f * M_PI * fmod(apu->ch3_phase, 1.0));
    }

    if (apu->ch4_enabled) {
        mix += noise_sample(&apu->noise_lfsr);
    }

    // Normalize mix
    mix *= 0.25f * apu->volume;

    // Output simple stereo panning (left/right equal)
    apu->left = mix;
    apu->right = mix;
}

// --- Retrieve current audio samples ---
float gb_apu_sample_left(gb_apu_t *apu) {
    return apu->left;
}

float gb_apu_sample_right(gb_apu_t *apu) {
    return apu->right;
}
