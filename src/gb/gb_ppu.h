#ifndef GB_PPU_H
#define GB_PPU_H

#include <stdint.h>

typedef struct {
    uint8_t scanline;
    uint8_t mode;
    uint32_t framebuffer[160 * 144];
} gb_ppu_t;

void gb_ppu_reset(gb_ppu_t *ppu);
void gb_ppu_tick(gb_ppu_t *ppu);

#endif // GB_PPU_H
