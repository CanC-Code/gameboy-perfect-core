#ifndef GBA_PPU_H
#define GBA_PPU_H

#include <stdint.h>
#include <stddef.h>

#define GBA_WIDTH 240
#define GBA_HEIGHT 160

typedef struct {
    uint32_t framebuffer[GBA_HEIGHT][GBA_WIDTH];
    // Add other PPU state as needed (BG, OBJ, layers)
} gba_ppu_t;

// Initialize PPU with pointer to MMU (if needed)
void gba_ppu_init(gba_ppu_t *ppu, void *mmu);

// Reset PPU state
void gba_ppu_reset(gba_ppu_t *ppu);

// Step PPU for a single frame / scanline
void gba_ppu_step(gba_ppu_t *ppu);

#endif // GBA_PPU_H
