#ifndef GB_PPU_H
#define GB_PPU_H

#include <stdint.h>
#include "core_common.h"
#include "cpu.h"

typedef struct {
    pixel_t framebuffer[GB_WIDTH * GB_HEIGHT];
    int scanline;
    bool vblank_flag;
} gb_ppu_t;

void gb_ppu_init(gb_ppu_t *ppu);
void gb_ppu_reset(gb_ppu_t *ppu);
void gb_ppu_step(gb_ppu_t *ppu, gb_cpu_t *cpu, int cycles);
void gb_ppu_render_scanline(gb_ppu_t *ppu, gb_cpu_t *cpu);

#endif // GB_PPU_H
