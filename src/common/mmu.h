#ifndef GB_MMU_H
#define GB_MMU_H

#include <stdint.h>
#include "core_state.h"

// Sizes for various memory regions
#define ROM_SIZE_MAX   0x8000  // 32KB for basic Gameboy ROM banking
#define VRAM_SIZE      0x2000  // 8KB
#define EXTRAM_SIZE    0x2000  // External cartridge RAM
#define WRAM_SIZE      0x2000  // Work RAM (internal)
#define OAM_SIZE       0xA0    // Sprite attribute table
#define IO_SIZE        0x80    // I/O registers
#define HRAM_SIZE      0x7F    // High RAM

typedef struct gb_mmu_s {
    uint8_t rom[ROM_SIZE_MAX];
    uint8_t vram[VRAM_SIZE];
    uint8_t eram[EXTRAM_SIZE];
    uint8_t wram[WRAM_SIZE];
    uint8_t oam[OAM_SIZE];
    uint8_t io[IO_SIZE];
    uint8_t hram[HRAM_SIZE];
    uint8_t ie;          // Interrupt Enable register
} gb_mmu_t;

// Initialize MMU
void gb_mmu_reset(gb_mmu_t *mmu);

// Read a byte from memory (address in 0x0000-0xFFFF)
uint8_t gb_mmu_read_byte(gb_mmu_t *mmu, uint16_t addr);

// Write a byte to memory (address in 0x0000-0xFFFF)
void gb_mmu_write_byte(gb_mmu_t *mmu, uint16_t addr, uint8_t val);

// Read a word (16-bit) from memory
uint16_t gb_mmu_read_word(gb_mmu_t *mmu, uint16_t addr);

// Write a word (16-bit) to memory
void gb_mmu_write_word(gb_mmu_t *mmu, uint16_t addr, uint16_t val);

#endif // GB_MMU_H
