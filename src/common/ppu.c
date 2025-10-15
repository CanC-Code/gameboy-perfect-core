#include "ppu.h"
#include <string.h>

void gb_ppu_reset(gb_ppu_t *ppu) {
    if (!ppu) return;
    memset(ppu, 0, sizeof(gb_ppu_t));
}

void gb_ppu_step(gb_ppu_t *ppu) {
    if (!ppu) return;
    memset(ppu->framebuffer, 0, 160*144*sizeof(uint16_t));
}
