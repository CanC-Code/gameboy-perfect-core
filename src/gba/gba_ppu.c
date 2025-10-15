#include "gba_ppu.h"
#include <string.h>

void gba_ppu_init(gba_ppu_t *ppu, void *mmu) {
    (void)mmu; // unused in skeleton
    memset(ppu->framebuffer, 0, sizeof(ppu->framebuffer));
}

void gba_ppu_reset(gba_ppu_t *ppu) {
    memset(ppu->framebuffer, 0, sizeof(ppu->framebuffer));
}

// Simple PPU step; fills framebuffer with dummy gradient for now
void gba_ppu_step(gba_ppu_t *ppu) {
    for(int y = 0; y < GBA_HEIGHT; y++) {
        for(int x = 0; x < GBA_WIDTH; x++) {
            uint8_t r = (x * 255) / GBA_WIDTH;
            uint8_t g = (y * 255) / GBA_HEIGHT;
            uint8_t b = ((x + y) * 255) / (GBA_WIDTH + GBA_HEIGHT);
            ppu->framebuffer[y][x] = (0xFF << 24) | (r << 16) | (g << 8) | b;
        }
    }
}
