#ifndef CORE_STATE_H
#define CORE_STATE_H

#include "core_common.h"
#include <stdint.h>
#include <stddef.h>

typedef struct {
    core_mode_t mode;
    uint8_t *rom;
    size_t rom_size;

    // native framebuffer pointer (owned)
    pixel_t *framebuffer;
    size_t fb_width;
    size_t fb_height;

    // cycle accounting
    uint64_t cycles_per_frame;
    uint64_t cycles_accum;

    // memory
    // mmu functions are provided in mmu.c
} core_state_t;

void core_init_state(core_state_t *cs, core_mode_t mode);
void core_unload_state(core_state_t *cs);
bool core_load_rom(core_state_t *cs, const void *data, size_t size);

#endif // CORE_STATE_H
