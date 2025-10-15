#ifndef GB_PPU_H
#define GB_PPU_H

#include <stdint.h>
#include <stdbool.h>
#include "../common/core_common.h"

#define GB_TILE_SIZE 8
#define GB_NUM_TILES 384
#define GB_SPRITES 40

typedef struct {
    uint8_t vram[0x2000];      // VRAM 8KB
    uint8_t oam[0xA0];         // Object Attribute Memory (sprites)
    uint8_t lcdc;              // LCD Control
    uint8_t stat;              // LCD Status
    uint8_t scy, scx;          // Scroll Y/X
    uint8_t ly, lyc;           // Current scanline / compare
    uint8_t wy, wx;            // Window position
    uint8_t bgp;               // BG Palette
    uint8_t obp0, obp1;        // Sprite palettes
    bool window_on;            // Window enable
    bool bg_on;                // Background enable
    bool sprites_on;           // Sprites enable
    pixel_t framebuffer[GB_WIDTH * GB_HEIGHT]; // Pixel buffer
} gb_ppu_t;

// Initialize PPU
void gb_ppu_init(gb_ppu_t *ppu);
void gb_ppu_reset(gb_ppu_t *ppu);

// Step one scanline (called per CPU cycles)
void gb_ppu_step_scanline(gb_ppu_t *ppu, uint16_t cycles);

// Render full frame
void gb_ppu_render_frame(gb_ppu_t *ppu);

#endif // GB_PPU_H
