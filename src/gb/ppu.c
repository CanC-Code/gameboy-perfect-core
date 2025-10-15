#include "ppu.h"
#include <string.h>

void gb_ppu_init(gb_ppu_t *ppu) {
    memset(ppu->framebuffer, 0, sizeof(ppu->framebuffer));
    ppu->scanline = 0;
    ppu->vblank_flag = false;
}

void gb_ppu_reset(gb_ppu_t *ppu) {
    gb_ppu_init(ppu);
}

void gb_ppu_step(gb_ppu_t *ppu, gb_cpu_t *cpu, int cycles) {
    // Each scanline = 456 cycles
    static int line_cycles = 0;
    line_cycles += cycles;
    if (line_cycles >= 456) {
        line_cycles -= 456;
        gb_ppu_render_scanline(ppu, cpu);
        ppu->scanline++;
        if (ppu->scanline == 144) ppu->vblank_flag = true;
        if (ppu->scanline >= 154) ppu->scanline = 0, ppu->vblank_flag = false;
    }
}

void gb_ppu_render_scanline(gb_ppu_t *ppu, gb_cpu_t *cpu) {
    // For now, fill the scanline with a checker pattern
    for (int x = 0; x < GB_WIDTH; x++) {
        int index = ppu->scanline * GB_WIDTH + x;
        ppu->framebuffer[index] = ((x + ppu->scanline) % 2) ? 0xFFFFFFFF : 0xFF000000;
    }
}
