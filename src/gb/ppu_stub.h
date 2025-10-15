#ifndef GB_PPU_STUB_H
#define GB_PPU_STUB_H

#include "core_common.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

struct gb_ppu_t {
    pixel_t *framebuffer;
    size_t width;
    size_t height;
    uint8_t scanline;
    bool vblank;
};

// Initialize PPU state
void gb_ppu_init(struct gb_ppu_t *ppu, size_t width, size_t height);

// Render one scanline (stub)
void gb_ppu_step(struct gb_ppu_t *ppu);

#endif // GB_PPU_STUB_H
