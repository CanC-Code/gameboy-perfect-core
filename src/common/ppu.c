#include "ppu.h"
#include "core_state.h"
#include <string.h>
#include <stdint.h>

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 144
#define CYCLES_PER_SCANLINE 456
#define TOTAL_SCANLINES 154

// Reset PPU state
void gb_ppu_reset(gb_ppu_t *ppu) {
    if (!ppu) return;
    memset(ppu, 0, sizeof(gb_ppu_t));
}

// Step the PPU for a number of CPU cycles
void gb_ppu_step(gb_ppu_t *ppu, int cycles) {
    if (!ppu) return;

    ppu->cycle += cycles;

    while (ppu->cycle >= CYCLES_PER_SCANLINE) {
        ppu->cycle -= CYCLES_PER_SCANLINE;
        ppu->line++;

        if (ppu->line < SCREEN_HEIGHT) {
            // Render this scanline to framebuffer
            // For simplicity, fill with some dummy data for now
            for (int x = 0; x < SCREEN_WIDTH; x++) {
                ppu->framebuffer[ppu->line * SCREEN_WIDTH + x] = 0; // Replace 0 with actual pixel rendering logic
            }
        }

        if (ppu->line == SCREEN_HEIGHT) {
            ppu->frame_ready = 1; // Frame is ready to be drawn
        }

        if (ppu->line >= TOTAL_SCANLINES) {
            ppu->line = 0; // Restart vertical scanlines
        }
    }
}

// Query if a frame is ready
int gb_ppu_frame_ready(gb_ppu_t *ppu) {
    if (!ppu) return 0;
    if (ppu->frame_ready) {
        ppu->frame_ready = 0; // Reset flag
        return 1;
    }
    return 0;
}
