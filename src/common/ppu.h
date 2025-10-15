#ifndef PPU_H
#define PPU_H

#include <stdint.h>

typedef struct gb_ppu_s {
    uint16_t framebuffer[160*144];
} gb_ppu_t;

void gb_ppu_reset(gb_ppu_t *ppu);
void gb_ppu_step(gb_ppu_t *ppu);

#endif /* PPU_H */
