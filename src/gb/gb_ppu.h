#ifndef GB_PPU_H
#define GB_PPU_H

#include <stdint.h>
#include <stdbool.h>

// LCD dimensions
#define GB_LCD_WIDTH 160
#define GB_LCD_HEIGHT 144

// Game Boy PPU (Picture Processing Unit) state
typedef struct gb_ppu_s {
    uint8_t lcdc;  // LCD Control
    uint8_t stat;  // LCD Status
    uint8_t scy;   // Scroll Y
    uint8_t scx;   // Scroll X
    uint8_t ly;    // LCD Y coordinate
    uint8_t lyc;   // LY Compare
    uint8_t bgp;   // BG Palette
    uint8_t obp0;  // Object Palette 0
    uint8_t obp1;  // Object Palette 1
    uint8_t wy;    // Window Y position
    uint8_t wx;    // Window X position
    uint8_t vram[0x2000]; // VRAM
    uint8_t oam[0xA0];    // Object Attribute Memory
} gb_ppu_t;

// Functions
void gb_ppu_init(gb_ppu_t *ppu);
void gb_ppu_reset(gb_ppu_t *ppu);
void gb_ppu_tick(gb_ppu_t *ppu, int cycles);
void gb_ppu_render_scanline(gb_ppu_t *ppu);

#endif // GB_PPU_H
