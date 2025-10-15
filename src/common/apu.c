#include "apu.h"
#include <string.h>

void gb_apu_reset(gb_apu_t *apu) {
    if (!apu) return;
    memset(apu, 0, sizeof(gb_apu_t));
}

void gb_apu_step(gb_apu_t *apu) {
    (void)apu;
    // Stub: silence
}
