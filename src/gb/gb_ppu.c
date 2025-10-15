#include "gb_ppu.h"
#include <string.h> // for memset

void gb_ppu_init(gb_ppu_t *ppu) {
    if (!ppu) return;
    memset(ppu, 0, sizeof(gb_ppu_t));
}

void gb_ppu_reset(gb_ppu_t *ppu) {
    if (!ppu) return;
    memset(ppu, 0, sizeof(gb_ppu_t));
}

void gb_ppu_tick(gb_ppu_t *ppu, int cycles) {
    (void)ppu;
    (void)cycles;
    // Stub: placeholder for timing and rendering logic
}

void gb_ppu_render_scanline(gb_ppu_t *ppu) {
    (void)ppu;
    // Stub: would draw one line of pixels to framebuffer
}
