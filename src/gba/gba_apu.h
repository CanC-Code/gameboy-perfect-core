#ifndef GBA_APU_H
#define GBA_APU_H

#include <stdint.h>

typedef struct {
    // Simple audio buffer
    int16_t buffer[4096];
    size_t buffer_pos;
} gba_apu_t;

// Initialize APU
void gba_apu_init(gba_apu_t *apu);

// Reset
void gba_apu_reset(gba_apu_t *apu);

// Step audio cycles
void gba_apu_step(gba_apu_t *apu, int cycles);

#endif // GBA_APU_H
