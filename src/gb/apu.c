#include "apu.h"
#include <string.h>

void gb_apu_init(gb_apu_t *apu) {
    memset(apu, 0, sizeof(*apu));
}

void gb_apu_reset(gb_apu_t *apu) {
    memset(apu, 0, sizeof(*apu));
}

void gb_apu_step(gb_apu_t *apu, int cycles) {
    // Advance APU timing; for simplicity we accumulate samples
    apu->buffer_pos += cycles;
    if (apu->buffer_pos > 512) apu->buffer_pos = 512;
}

void gb_apu_generate_samples(gb_apu_t *apu, int16_t *out_buffer, size_t samples) {
    // Fill out_buffer with simple silence for now (to be replaced by full channels)
    for (size_t i = 0; i < samples; i++) {
        out_buffer[i] = 0;
    }
    apu->buffer_pos = 0;
}
