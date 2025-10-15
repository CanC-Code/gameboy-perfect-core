#include "gb_ppu.h"
#include <string.h>

// Initialize PPU
void gb_ppu_init(gb_ppu_t *ppu) {
    memset(ppu, 0, sizeof(gb_ppu_t));
    ppu->bg_on = true;
    ppu->sprites_on = true;
    ppu->window_on = false;
}

void gb_ppu_reset(gb_ppu_t *ppu) {
    gb_ppu_init(ppu);
}

// Helper: get BG color from palette
static pixel_t gb_ppu_map_color(uint8_t palette, uint8_t color) {
    // 2-bit color value: 0-3
    switch ((palette >> (color * 2)) & 3) {
        case 0: return 0xFFFFFFFF; // White
        case 1: return 0xAAAAAAFF; // Light gray
        case 2: return 0x555555FF; // Dark gray
        case 3: return 0x000000FF; // Black
    }
    return 0xFFFFFFFF;
}

// Render one scanline background
static void gb_ppu_render_bg_scanline(gb_ppu_t *ppu) {
    uint16_t y = ppu->ly;
    if (!ppu->bg_on) return;

    uint16_t base_addr = 0x1800; // example for BG tilemap
    for (uint16_t x = 0; x < GB_WIDTH; x++) {
        uint16_t tile_x = (x + ppu->scx) / GB_TILE_SIZE;
        uint16_t tile_y = (y + ppu->scy) / GB_TILE_SIZE;
        uint16_t tile_index = tile_y * 32 + tile_x;
        uint8_t tile_id = ppu->vram[base_addr + tile_index];

        uint8_t line = (y + ppu->scy) % GB_TILE_SIZE;
        uint8_t byte1 = ppu->vram[tile_id * 16 + line * 2];
        uint8_t byte2 = ppu->vram[tile_id * 16 + line * 2 + 1];
        uint8_t bit = 7 - ((x + ppu->scx) % 8);
        uint8_t color = ((byte2 >> bit) & 1) << 1 | ((byte1 >> bit) & 1);
        ppu->framebuffer[y * GB_WIDTH + x] = gb_ppu_map_color(ppu->bgp, color);
    }
}

// Render window scanline
static void gb_ppu_render_window_scanline(gb_ppu_t *ppu) {
    if (!ppu->window_on) return;
    uint16_t y = ppu->ly;
    if (y < ppu->wy) return;

    uint16_t base_addr = 0x1C00; // example window tilemap
    for (uint16_t x = 0; x < GB_WIDTH; x++) {
        if (x + 7 < ppu->wx) continue;
        uint16_t tile_x = (x - ppu->wx) / GB_TILE_SIZE;
        uint16_t tile_y = (y - ppu->wy) / GB_TILE_SIZE;
        uint16_t tile_index = tile_y * 32 + tile_x;
        uint8_t tile_id = ppu->vram[base_addr + tile_index];

        uint8_t line = (y - ppu->wy) % GB_TILE_SIZE;
        uint8_t byte1 = ppu->vram[tile_id * 16 + line * 2];
        uint8_t byte2 = ppu->vram[tile_id * 16 + line * 2 + 1];
        uint8_t bit = 7 - ((x - ppu->wx) % 8);
        uint8_t color = ((byte2 >> bit) & 1) << 1 | ((byte1 >> bit) & 1);
        ppu->framebuffer[y * GB_WIDTH + x] = gb_ppu_map_color(ppu->bgp, color);
    }
}

// Render sprites on scanline
static void gb_ppu_render_sprites_scanline(gb_ppu_t *ppu) {
    if (!ppu->sprites_on) return;
    uint16_t y = ppu->ly;

    for (int i = 0; i < GB_SPRITES; i++) {
        uint8_t *sprite = &ppu->oam[i * 4];
        int sprite_y = sprite[0] - 16;
        int sprite_x = sprite[1] - 8;
        uint8_t tile = sprite[2];
        uint8_t attr = sprite[3];

        if (y < sprite_y || y >= sprite_y + 8) continue;

        int line = y - sprite_y;
        if (attr & 0x40) line = 7 - line; // vertical flip

        uint8_t byte1 = ppu->vram[tile * 16 + line * 2];
        uint8_t byte2 = ppu->vram[tile * 16 + line * 2 + 1];

        for (int px = 0; px < 8; px++) {
            int x = sprite_x + px;
            if (x < 0 || x >= GB_WIDTH) continue;
            int bit = 7 - px;
            if (attr & 0x20) bit = px; // horizontal flip
            uint8_t color = ((byte2 >> bit) & 1) << 1 | ((byte1 >> bit) & 1);
            if (color == 0) continue; // transparent
            pixel_t mapped = gb_ppu_map_color(attr & 0x10 ? ppu->obp1 : ppu->obp0, color);
            ppu->framebuffer[y * GB_WIDTH + x] = mapped;
        }
    }
}

// Step one scanline
void gb_ppu_step_scanline(gb_ppu_t *ppu, uint16_t cycles) {
    ppu->ly++;
    if (ppu->ly >= GB_HEIGHT) {
        ppu->ly = 0;
    }
}

// Render full frame
void gb_ppu_render_frame(gb_ppu_t *ppu) {
    for (ppu->ly = 0; ppu->ly < GB_HEIGHT; ppu->ly++) {
        gb_ppu_render_bg_scanline(ppu);
        gb_ppu_render_window_scanline(ppu);
        gb_ppu_render_sprites_scanline(ppu);
    }
}
