#include "core_state.h"
#include <stdlib.h>
#include <string.h>

#include "cpu_stub.h"
#include "ppu_stub.h"

// --- Internal helpers ---

uint64_t cycles_per_frame_for_mode(core_mode_t mode) {
    switch (mode) {
        case MODE_GB:
        case MODE_GBC:
            return 70224; // GB cycles per frame (approx 59.73 Hz)
        case MODE_GBA:
            return 280896; // GBA cycles per frame (approx 59.73 Hz)
        default:
            return 0;
    }
}

// --- Core functions ---

void core_init_state(core_state_t *cs, core_mode_t mode) {
    if (!cs) return;

    cs->mode = mode;
    cs->rom = NULL;
    cs->rom_size = 0;
    cs->framebuffer = NULL;

    switch (mode) {
        case MODE_GB:
        case MODE_GBC:
            cs->fb_width  = GB_WIDTH;
            cs->fb_height = GB_HEIGHT;
            cs->cycles_per_frame = cycles_per_frame_for_mode(mode);

            // Allocate GB CPU + PPU
            cs->gb_cpu = malloc(sizeof(struct gb_cpu_t));
            cs->gb_ppu = malloc(sizeof(struct gb_ppu_t));
            if (cs->gb_cpu) gb_cpu_init(cs->gb_cpu);
            if (cs->gb_ppu) gb_ppu_init(cs->gb_ppu, cs->fb_width, cs->fb_height);

            cs->gba_cpu = NULL;
            cs->gba_ppu = NULL;
            break;

        case MODE_GBA:
            cs->fb_width  = GBA_WIDTH;
            cs->fb_height = GBA_HEIGHT;
            cs->cycles_per_frame = cycles_per_frame_for_mode(mode);

            cs->gba_cpu = malloc(sizeof(struct gba_cpu_t));
            cs->gba_ppu = malloc(sizeof(struct gba_ppu_t));
            if (cs->gba_cpu) gba_cpu_init(cs->gba_cpu);
            if (cs->gba_ppu) gba_ppu_init(cs->gba_ppu, cs->fb_width, cs->fb_height);

            cs->gb_cpu = NULL;
            cs->gb_ppu = NULL;
            break;

        default:
            cs->gb_cpu = cs->gb_ppu = NULL;
            cs->gba_cpu = cs->gba_ppu = NULL;
            cs->cycles_per_frame = 0;
            cs->fb_width = cs->fb_height = 0;
            break;
    }

    // Allocate framebuffer
    cs->framebuffer = malloc(sizeof(pixel_t) * cs->fb_width * cs->fb_height);
    if (cs->framebuffer) memset(cs->framebuffer, 0, sizeof(pixel_t) * cs->fb_width * cs->fb_height);

    cs->cycles_accum = 0;
}

void core_unload_state(core_state_t *cs) {
    if (!cs) return;

    if (cs->gb_cpu) { free(cs->gb_cpu); cs->gb_cpu = NULL; }
    if (cs->gb_ppu) { free(cs->gb_ppu); cs->gb_ppu = NULL; }
    if (cs->gba_cpu) { free(cs->gba_cpu); cs->gba_cpu = NULL; }
    if (cs->gba_ppu) { free(cs->gba_ppu); cs->gba_ppu = NULL; }

    if (cs->framebuffer) { free(cs->framebuffer); cs->framebuffer = NULL; }

    cs->rom = NULL;
    cs->rom_size = 0;
    cs->cycles_accum = 0;
    cs->mode = MODE_UNSET;
}

bool core_load_rom(core_state_t *cs, const void *data, size_t size) {
    if (!cs || !data || size == 0) return false;

    uint8_t *new_rom = malloc(size);
    if (!new_rom) return false;

    memcpy(new_rom, data, size);

    if (cs->rom) free(cs->rom);
    cs->rom = new_rom;
    cs->rom_size = size;

    return true;
}
