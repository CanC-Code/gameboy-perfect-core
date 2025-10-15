#ifndef CORE_STATE_H
#define CORE_STATE_H

#include "core_common.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

// Forward declare GB/GBA CPU/PPU structs
struct gb_cpu_t;
struct gb_ppu_t;
struct gba_cpu_t;
struct gba_ppu_t;

typedef struct {
    core_mode_t mode;

    // ROM
    uint8_t *rom;
    size_t rom_size;

    // Framebuffer
    pixel_t *framebuffer;
    size_t fb_width;
    size_t fb_height;

    // Cycle accounting
    uint64_t cycles_per_frame;
    uint64_t cycles_accum;

    // GB/GBC CPU + PPU state
    struct gb_cpu_t *gb_cpu;
    struct gb_ppu_t *gb_ppu;

    // GBA CPU + PPU state
    struct gba_cpu_t *gba_cpu;
    struct gba_ppu_t *gba_ppu;

} core_state_t;

// Core functions
void core_init_state(core_state_t *cs, core_mode_t mode);
void core_unload_state(core_state_t *cs);
bool core_load_rom(core_state_t *cs, const void *data, size_t size);

// Helper
uint64_t cycles_per_frame_for_mode(core_mode_t mode);

#endif // CORE_STATE_H
