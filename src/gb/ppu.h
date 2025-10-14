#ifndef GB_PPU_H
#define GB_PPU_H

#include "../common/core_state.h"
#include "mmu.h"
#include <stdint.h>
#include <stdbool.h>

#define GB_SCREEN_WIDTH  160
#define GB_SCREEN_HEIGHT 144
#define MAX_SPRITES 40

typedef struct {
    /* LCD Control (LCDC) */
    uint8_t lcdc;
    uint8_t stat;

    uint8_t scy;
    uint8_t scx;
    uint8_t ly;
    uint8_t lyc;

    uint8_t bgp;
    uint8_t obp0;
    uint8_t obp1;

    uint8_t wy;
    uint8_t wx;

    bool lcd_enabled;

} gb_ppu_t;

/* Initialize/reset PPU state */
void gb_ppu_init(core_state_t *cs);
void gb_ppu_reset(core_state_t *cs);

/* Step PPU for N CPU cycles */
void gb_ppu_step(core_state_t *cs, int cycles);

/* Render a full frame */
void gb_ppu_render_frame(core_state_t *cs);

#endif /* GB_PPU_H */
