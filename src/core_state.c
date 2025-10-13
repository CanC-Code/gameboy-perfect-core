#include "core_state.h"
#include "core_common.h"
#include <stdlib.h>
#include <string.h>

// forward declarations for mode timing
static uint64_t cycles_per_frame_for_mode(core_mode_t m);

void core_init_state(core_state_t *cs, core_mode_t mode) {
    memset(cs, 0, sizeof(*cs));
    cs->mode = mode;
    cs->framebuffer = NULL;
    cs->fb_width = (mode == MODE_GBA) ? GBA_WIDTH : GB_WIDTH;
    cs->fb_height = (mode == MODE_GBA) ? GBA_HEIGHT : GB_HEIGHT;
    cs->cycles_per_frame = cycles_per_frame_for_mode(mode);
    cs->cycles_accum = 0;
}

void core_unload_state(core_state_t *cs) {
    if (!cs) return;
    if (cs->rom) { free(cs->rom); cs->rom = NULL; cs->rom_size = 0; }
    if (cs->framebuffer) { free(cs->framebuffer); cs->framebuffer = NULL; }
    cs->mode = MODE_UNSET;
}

bool core_load_rom(core_state_t *cs, const void *data, size_t size) {
    if (!cs || !data || size == 0) return false;
    cs->rom = (uint8_t*)malloc(size);
    if (!cs->rom) return false;
    memcpy(cs->rom, data, size);
    cs->rom_size = size;
    // framebuffer allocate
    size_t pixels = cs->fb_width * cs->fb_height;
    cs->framebuffer = (pixel_t*)malloc(pixels * sizeof(pixel_t));
    if (!cs->framebuffer) { free(cs->rom); cs->rom = NULL; cs->rom_size = 0; return false; }
    memset(cs->framebuffer, 0, pixels * sizeof(pixel_t));
    return true;
}

static uint64_t cycles_per_frame_for_mode(core_mode_t m) {
    // Use classic cycles-per-frame:
    // GB (DMG): CPU clock ? 4.194304 MHz, ~70224 cycles/frame (for 59.73 Hz)
    // GBA: ARM7TDMI clock ~16.78 MHz, 280896 cycles/frame (approx). We'll choose common values.
    switch (m) {
        case MODE_GBA: return 16777216ULL / 60ULL; // approximate for 59.7fps -> approx 279620
        default: return 4194304ULL / 60ULL; // ~69905 -> use integer division as budget
    }
}
