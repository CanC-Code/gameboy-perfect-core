#include "core_state.h"
#include "core_common.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// forward declarations for mode timing
static uint64_t cycles_per_frame_for_mode(core_mode_t m);

void core_init_state(core_state_t *cs, core_mode_t mode) {
    if (!cs) return;
    memset(cs, 0, sizeof(*cs));

    cs->mode = mode;
    cs->framebuffer = NULL;

    // Determine framebuffer dimensions
    switch (mode) {
        case MODE_GBA:
            cs->fb_width = GBA_WIDTH;
            cs->fb_height = GBA_HEIGHT;
            break;
        case MODE_GBC:
        case MODE_GB:
        default:
            cs->fb_width = GB_WIDTH;
            cs->fb_height = GB_HEIGHT;
            break;
    }

    cs->cycles_per_frame = cycles_per_frame_for_mode(mode);
    cs->cycles_accum = 0;
}

void core_unload_state(core_state_t *cs) {
    if (!cs) return;

    if (cs->rom) {
        free(cs->rom);
        cs->rom = NULL;
        cs->rom_size = 0;
    }

    if (cs->framebuffer) {
        free(cs->framebuffer);
        cs->framebuffer = NULL;
    }

    cs->mode = MODE_UNSET;
}

bool core_load_rom(core_state_t *cs, const void *data, size_t size) {
    if (!cs || !data || size == 0) return false;

    cs->rom = (uint8_t*)malloc(size);
    if (!cs->rom) return false;

    memcpy(cs->rom, data, size);
    cs->rom_size = size;

    // Allocate framebuffer memory
    size_t pixels = (size_t)cs->fb_width * (size_t)cs->fb_height;
    cs->framebuffer = (pixel_t*)malloc(pixels * sizeof(pixel_t));
    if (!cs->framebuffer) {
        free(cs->rom);
        cs->rom = NULL;
        cs->rom_size = 0;
        return false;
    }

    memset(cs->framebuffer, 0, pixels * sizeof(pixel_t));
    return true;
}

static uint64_t cycles_per_frame_for_mode(core_mode_t m) {
    // Approximate CPU cycles per frame for each platform
    switch (m) {
        case MODE_GBA:
            // ARM7TDMI ~16.78 MHz, ~280,896 cycles/frame @59.7 Hz
            return 16777216ULL / 60ULL;
        case MODE_GBC:
            // Same clock as DMG, slightly different timings
            return 4194304ULL / 60ULL;
        case MODE_GB:
        default:
            // DMG ~4.19 MHz, ~70224 cycles/frame
            return 4194304ULL / 60ULL;
    }
}
