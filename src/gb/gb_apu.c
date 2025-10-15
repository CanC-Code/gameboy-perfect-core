#include "gb_apu.h"
#include <stdint.h>

void gb_apu_reset(gb_apu_t *apu) {
    for (int i = 0; i < 4; i++) {
        apu->channels[i].enabled = false;
        apu->channels[i].volume = 0;
        apu->channels[i].length = 0;
    }
}

void gb_apu_tick(gb_apu_t *apu) {
    for (int i = 0; i < 4; i++) {
        if (!apu->channels[i].enabled) continue;
        if (apu->channels[i].length > 0) apu->channels[i].length--;
        // Implement square, wave, noise generation per channel
    }
}
