#include "gb_apu.h"
#include <string.h>
#include <math.h>

// Sample rate
#define GB_SAMPLE_RATE 44100
#define GB_CPU_FREQ 4194304 // 4.194304 MHz

void gb_apu_init(gb_apu_t *apu) {
    memset(apu, 0, sizeof(gb_apu_t));
    apu->square1.enabled = false;
    apu->square2.enabled = false;
    apu->wave.enabled = false;
    apu->noise.enabled = false;
}

void gb_apu_reset(gb_apu_t *apu) {
    gb_apu_init(apu);
}

static int generate_square(int phase, uint8_t duty) {
    // duty: 0-3 (12.5%, 25%, 50%, 75%)
    static const float duty_table[4][8] = {
        {1,0,0,0,0,0,0,0}, // 12.5%
        {1,1,0,0,0,0,0,0}, // 25%
        {1,1,1,1,0,0,0,0}, // 50%
        {0,1,1,1,1,1,1,0}  // 75%
    };
    return duty_table[duty & 3][phase & 7] ? 1 : -1;
}

static int generate_noise(int phase) {
    // Simple pseudo-random noise
    return ((phase & 1) ? 1 : -1);
}

void gb_apu_step(gb_apu_t *apu, int cycles) {
    for (int i = 0; i < cycles; i++) {
        // Advance phase for each channel
        if (apu->square1.enabled) apu->square1.phase++;
        if (apu->square2.enabled) apu->square2.phase++;
        if (apu->wave.enabled) apu->wave.phase++;
        if (apu->noise.enabled) apu->noise.phase++;

        // Simple mixing
        int sample = 0;
        if (apu->square1.enabled) sample += generate_square(apu->square1.phase, apu->square1.duty) * apu->square1.volume;
        if (apu->square2.enabled) sample += generate_square(apu->square2.phase, apu->square2.duty) * apu->square2.volume;
        if (apu->wave.enabled)   sample += apu->wave.enabled ? apu->wave.volume : 0;
        if (apu->noise.enabled)  sample += generate_noise(apu->noise.phase) * apu->noise.volume;

        // Write to buffer
        if (apu->buffer_pos < GB_AUDIO_BUFFER_SIZE) {
            apu->buffer[apu->buffer_pos++] = sample;
        }
    }
}

void gb_apu_mix(gb_apu_t *apu, int16_t *out_buffer, size_t samples) {
    for (size_t i = 0; i < samples && i < apu->buffer_pos; i++) {
        out_buffer[i] = apu->buffer[i];
    }
    apu->buffer_pos = 0; // reset buffer
}
