#ifndef GB_PPU_H
#define GB_PPU_H

#include <stdint.h>

typedef struct {
    uint8_t vram[0x2000];
    uint8_t oam[0xA0];
    int scanline;
} gb_ppu_t;

void gb_ppu_reset(gb_ppu_t *ppu);
void gb_ppu_tick(gb_ppu_t *ppu);

#endif // GB_PPU_H
