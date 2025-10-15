#include "ppu_stub.h"
#include <string.h>

void gb_ppu_init(struct gb_ppu_t *ppu, size_t width, size_t height) {
    if (!ppu) return;
    ppu->width = width;
    ppu->height = height;
    ppu->scanline = 0;
    ppu->vblank = false;
    ppu->framebuffer = malloc(sizeof(pixel_t) * width * height);
    if (ppu->framebuffer) {
        memset(ppu->framebuffer, 0, sizeof(pixel_t) * width * height);
    }
}

void gb_ppu_step(struct gb_ppu_t *ppu) {
    if (!ppu) return;

    // Stub: increment scanline and toggle V-Blank
    ppu->scanline++;
    if (ppu->scanline >= ppu->height) {
        ppu->scanline = 0;
        ppu->vblank = !ppu->vblank;
    }
}
