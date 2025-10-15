#ifndef GB_APU_H
#define GB_APU_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct {
    // Simple 4-channel GB APU
    uint8_t nr10, nr11, nr12, nr13, nr14;
    uint8_t nr21, nr22, nr23, nr24;
    uint8_t nr30, nr31, nr32, nr33, nr34;
    uint8_t nr41, nr42, nr43, nr44;
    uint8_t nr50, nr51, nr52;

    int16_t sample_buffer[512];
    size_t buffer_pos;
} gb_apu_t;

void gb_apu_init(gb_apu_t *apu);
void gb_apu_reset(gb_apu_t *apu);
void gb_apu_step(gb_apu_t *apu, int cycles);
void gb_apu_generate_samples(gb_apu_t *apu, int16_t *out_buffer, size_t samples);

#endif // GB_APU_H
