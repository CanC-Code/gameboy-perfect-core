#ifndef GB_APU_H
#define GB_APU_H

#include <stdint.h>
#include <stddef.h>
#include "../common/core_common.h"

#define AUDIO_BUFFER_SIZE 4096

typedef struct {
    int16_t sample_buffer[AUDIO_BUFFER_SIZE];
    size_t sample_count;
} gb_apu_t;

// Lifecycle
void gb_apu_init(gb_apu_t *apu);
void gb_apu_reset(gb_apu_t *apu);

// Per-cycle step
void gb_apu_step(gb_apu_t *apu, uint16_t cycles);

#endif // GB_APU_H
