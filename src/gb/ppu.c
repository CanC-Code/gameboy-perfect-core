#include "ppu.h"
#include "mmu.h"
#include <string.h>
#include <stdio.h>

static uint32_t gb_color_from_id(uint8_t palette, uint8_t id) {
    uint8_t shade = (palette >> (id * 2)) & 0x03;
    uint8_t v = 0xFF - (shade * 0x55);
    return 0xFF000000 | (v << 16) | (v << 8) | v;
}

/* Initialize/reset PPU state */
void gb_ppu_init(core_state_t *cs) {
    cs->ppu = malloc(sizeof(gb_ppu_t));
    if (!cs->ppu) return;
    memset(cs->ppu, 0, sizeof(gb_ppu_t));
}

void gb_ppu_reset(core_state_t *cs) {
    gb_ppu_t *ppu = (gb_ppu_t *)cs->ppu;
    if (!ppu) return;

    ppu->lcdc = 0x91;
    ppu->stat = 0;
    ppu->scx = 0;
    ppu->scy = 0;
    ppu->ly = 0;
    ppu->lyc = 0;
    ppu->bgp = 0xFC;
    ppu->obp0 = 0xFF;
    ppu->obp1 = 0xFF;
    ppu->wx = 7;
    ppu->wy = 0;
    ppu->lcd_enabled = true;
}

/* Render single scanline (BG + window + sprites) */
static void gb_ppu_render_scanline(core_state_t *cs) {
    gb_ppu_t *ppu = (gb_ppu_t *)cs->ppu;
    if (!ppu || !cs->framebuffer) return;

    uint8_t ly = ppu->ly;

    for (int x = 0; x < GB_SCREEN_WIDTH; x++) {
        uint8_t color_id = 0;

        /* Background */
        if (ppu->lcdc & 0x01) {
            uint16_t tilemap_base = (ppu->lcdc & 0x08) ? 0x9C00 : 0x9800;
            uint16_t tiledata_base = (ppu->lcdc & 0x10) ? 0x8000 : 0x8800;
            uint8_t scx = ppu->scx;
            uint8_t scy = ppu->scy;
            uint8_t tile_x = (x + scx) / 8;
            uint8_t tile_y = (ly + scy) / 8;
            uint16_t tile_index_addr = tilemap_base + tile_y * 32 + tile_x;
            uint8_t tile_index = mmu_read8(cs, tile_index_addr);
            uint16_t tile_addr = tiledata_base + tile_index * 16;
            uint8_t line = (ly + scy) % 8;
            uint8_t byte1 = mmu_read8(cs, tile_addr + line * 2);
            uint8_t byte2 = mmu_read8(cs, tile_addr + line * 2 + 1);
            uint8_t bit = 7 - ((x + scx) % 8);
            color_id = ((byte2 >> bit) & 1) << 1 | ((byte1 >> bit) & 1);
        }

        /* Window layer */
        if ((ppu->lcdc & 0x20) && ly >= ppu->wy && x >= (ppu->wx - 7)) {
            uint16_t win_tilemap_base = (ppu->lcdc & 0x40) ? 0x9C00 : 0x9800;
            uint8_t win_x = x - (ppu->wx - 7);
            uint8_t win_y = ly - ppu->wy;
            uint8_t tile_x = win_x / 8;
            uint8_t tile_y = win_y / 8;
            uint16_t tile_index_addr = win_tilemap_base + tile_y * 32 + tile_x;
            uint8_t tile_index = mmu_read8(cs, tile_index_addr);
            uint16_t tiledata_base = (ppu->lcdc & 0x10) ? 0x8000 : 0x8800;
            uint16_t tile_addr = tiledata_base + tile_index * 16;
            uint8_t line = win_y % 8;
            uint8_t byte1 = mmu_read8(cs, tile_addr + line * 2);
            uint8_t byte2 = mmu_read8(cs, tile_addr + line * 2 + 1);
            uint8_t bit = 7 - (win_x % 8);
            color_id = ((byte2 >> bit) & 1) << 1 | ((byte1 >> bit) & 1);
        }

        /* Sprites */
        if (ppu->lcdc & 0x02) {
            for (int i = 0; i < MAX_SPRITES; i++) {
                uint16_t oam_addr = 0xFE00 + i * 4;
                uint8_t sy = mmu_read8(cs, oam_addr) - 16;
                uint8_t sx = mmu_read8(cs, oam_addr + 1) - 8;
                uint8_t tile = mmu_read8(cs, oam_addr + 2);
                uint8_t attr = mmu_read8(cs, oam_addr + 3);

                bool xflip = attr & 0x20;
                bool yflip = attr & 0x40;
                bool use_obp1 = attr & 0x10;

                if (x >= sx && x < sx + 8 && ly >= sy && ly < sy + 8) {
                    uint16_t line = yflip ? 7 - (ly - sy) : (ly - sy);
                    uint16_t tile_addr = 0x8000 + tile * 16;
                    uint8_t byte1 = mmu_read8(cs, tile_addr + line * 2);
                    uint8_t byte2 = mmu_read8(cs, tile_addr + line * 2 + 1);
                    uint8_t bit = xflip ? x - sx : 7 - (x - sx);
                    uint8_t sprite_color_id = ((byte2 >> bit) & 1) << 1 | ((byte1 >> bit) & 1);
                    if (sprite_color_id != 0) {
                        color_id = sprite_color_id;
                        uint8_t palette = use_obp1 ? ppu->obp1 : ppu->obp0;
                        cs->framebuffer[ly * GB_SCREEN_WIDTH + x] = gb_color_from_id(palette, color_id);
                        goto next_pixel;
                    }
                }
            }
        }

        /* Final pixel */
        cs->framebuffer[ly * GB_SCREEN_WIDTH + x] = gb_color_from_id(ppu->bgp, color_id);
    next_pixel:;
    }
}

/* Step PPU and handle interrupts */
void gb_ppu_step(core_state_t *cs, int cycles) {
    gb_ppu_t *ppu = (gb_ppu_t *)cs->ppu;
    if (!ppu) return;

    static int cycle_accum = 0;
    cycle_accum += cycles;

    while (cycle_accum >= 456) {
        cycle_accum -= 456;

        if (ppu->lcd_enabled) {
            gb_ppu_render_scanline(cs);
        }

        ppu->ly++;
        if (ppu->ly >= 144) {
            /* V-Blank start */
            ppu->ly = 144;
            cs->vblank_flag = true;
            /* Trigger V-Blank interrupt */
            if (cs->interrupt_enable & 0x01)
                cs->interrupt_flag |= 0x01;
        }
        if (ppu->ly > 153) {
            ppu->ly = 0;
            cs->vblank_flag = false;
        }

        /* LY == LYC check */
        if (ppu->ly == ppu->lyc) {
            ppu->stat |= 0x04; // Set coincidence flag
            if (ppu->stat & 0x40) { // STAT interrupt enable
                cs->interrupt_flag |= 0x02;
            }
        } else {
            ppu->stat &= ~0x04;
        }
    }
}

/* Render full frame */
void gb_ppu_render_frame(core_state_t *cs) {
    gb_ppu_t *ppu = (gb_ppu_t *)cs->ppu;
    if (!ppu) return;

    for (ppu->ly = 0; ppu->ly < GB_SCREEN_HEIGHT; ppu->ly++) {
        gb_ppu_render_scanline(cs);
    }
}
