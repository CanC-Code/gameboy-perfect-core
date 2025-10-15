#ifndef GB_PPU_H
#define GB_PPU_H

#include <stdint.h>

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 144

typedef struct gb_ppu_s {
    uint16_t framebuffer[SCREEN_WIDTH * SCREEN_HEIGHT]; // Pixel data for screen
    int cycle;        // Current cycle within scanline
    int line;         // Current vertical scanline (0-153)
    int frame_ready;  // Flag indicating a frame is ready
} gb_ppu_t;

// Reset the PPU state
void gb_ppu_reset(gb_ppu_t *ppu);

// Step the PPU by a number of CPU cycles
void gb_ppu_step(gb_ppu_t *ppu, int cycles);

// Query if a frame is ready to be drawn
int gb_ppu_frame_ready(gb_ppu_t *ppu);

#endif // GB_PPU_H
