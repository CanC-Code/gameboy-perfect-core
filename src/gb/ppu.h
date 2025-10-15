#ifndef GB_PPU_H
#define GB_PPU_H

typedef struct gb_ppu_s {
    // Example PPU state
    unsigned char vram[0x2000];
    unsigned char lcd_control;
} gb_ppu_t;

void gb_ppu_reset( gb_ppu_t *ppu );

#endif // GB_PPU_H
