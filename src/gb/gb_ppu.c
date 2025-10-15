#include "gb_ppu.h"
#include "../common/core_state.h"

void gb_ppu_reset(gb_ppu_t *ppu) {
    ppu->scanline = 0;
    ppu->mode = 2;
    for (int i = 0; i < 160 * 144; i++) {
        ppu->framebuffer[i] = 0xFF; // White
    }
}

void gb_ppu_tick(gb_ppu_t *ppu) {
    ppu->scanline++;
    if (ppu->scanline >= 144) {
        ppu->mode = 1; // V-Blank
    } else {
        ppu->mode = 2; // OAM
        // Render background/window line
    }
}
