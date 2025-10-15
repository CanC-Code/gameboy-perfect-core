#ifndef GB_APU_H
#define GB_APU_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    bool enabled;
    uint8_t volume;
    uint16_t length;
} gb_channel_t;

typedef struct {
    gb_channel_t channels[4];
} gb_apu_t;

void gb_apu_reset(gb_apu_t *apu);
void gb_apu_tick(gb_apu_t *apu);

#endif // GB_APU_H
