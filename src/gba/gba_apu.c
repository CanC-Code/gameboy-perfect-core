#include "gba_apu.h"
#include <string.h>

void gba_apu_init(gba_apu_t *apu) {
    apu->buffer_pos = 0;
    memset(apu->buffer, 0, sizeof(apu->buffer));
}

void gba_apu_reset(gba_apu_t *apu) {
    apu->buffer_pos = 0;
    memset(apu->buffer, 0, sizeof(apu->buffer));
}

void gba_apu_step(gba_apu_t *apu, int cycles) {
    // Skeleton: just advance buffer position
    apu->buffer_pos = (apu->buffer_pos + cycles) % 4096;
}
