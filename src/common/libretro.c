// src/common/libretro.c
#include "core_common.h"
#include "core_state.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "libretro.h"

// ----------------- Global Core State -----------------
static core_state_t core;
static struct retro_game_info game_info;

// Callbacks provided by RetroArch
static retro_video_refresh_t video_cb;
static retro_audio_sample_t audio_cb;
static retro_audio_sample_batch_t audio_batch_cb;
static retro_input_state_t input_state_cb;
static retro_input_poll_t input_poll_cb;
static retro_environment_t environ_cb;

// Minimal button bitfield for GB joypad (user-defined mapping)
typedef enum {
    BUTTON_RIGHT = 1<<0,
    BUTTON_LEFT  = 1<<1,
    BUTTON_UP    = 1<<2,
    BUTTON_DOWN  = 1<<3,
    BUTTON_A     = 1<<4,
    BUTTON_B     = 1<<5,
    BUTTON_SELECT= 1<<6,
    BUTTON_START = 1<<7,
} gb_buttons_t;

// ----------------- Weak hooks (can be overridden by real implementations) -----------------
// GB functions
void gb_cpu_reset(core_state_t *cs) __attribute__((weak));
unsigned gb_cpu_exec_cycles(core_state_t *cs, unsigned max_cycles) __attribute__((weak));
void gb_ppu_step(core_state_t *cs, unsigned cycles) __attribute__((weak));
void gb_apu_step(core_state_t *cs, unsigned cycles) __attribute__((weak));
void gb_set_input_state(core_state_t *cs, uint16_t buttons) __attribute__((weak));

// GBA functions
void gba_cpu_reset(core_state_t *cs) __attribute__((weak));
unsigned gba_cpu_exec_cycles(core_state_t *cs, unsigned max_cycles) __attribute__((weak));
void gba_ppu_step(core_state_t *cs, unsigned cycles) __attribute__((weak));
void gba_sound_step(core_state_t *cs, unsigned cycles) __attribute__((weak));
void gba_set_input_state(core_state_t *cs, uint32_t buttons) __attribute__((weak));

// Default weak implementations (no-ops / minimal fallbacks)
void gb_cpu_reset(core_state_t *cs) { (void)cs; }
unsigned gb_cpu_exec_cycles(core_state_t *cs, unsigned max_cycles) { (void)cs; return max_cycles; }
void gb_ppu_step(core_state_t *cs, unsigned cycles) { (void)cs; (void)cycles; }
void gb_apu_step(core_state_t *cs, unsigned cycles) { (void)cs; (void)cycles; }
void gb_set_input_state(core_state_t *cs, uint16_t buttons) { (void)cs; (void)buttons; }

void gba_cpu_reset(core_state_t *cs) { (void)cs; }
unsigned gba_cpu_exec_cycles(core_state_t *cs, unsigned max_cycles) { (void)cs; return max_cycles; }
void gba_ppu_step(core_state_t *cs, unsigned cycles) { (void)cs; (void)cycles; }
void gba_sound_step(core_state_t *cs, unsigned cycles) { (void)cs; (void)cycles; }
void gba_set_input_state(core_state_t *cs, uint32_t buttons) { (void)cs; (void)buttons; }

// ----------------- RetroArch Required Functions -----------------

void retro_init(void) {
    memset(&core, 0, sizeof(core));
}

void retro_deinit(void) {
    core_unload_state(&core);
}

unsigned retro_api_version(void) {
    return RETRO_API_VERSION;
}

void retro_set_environment(retro_environment_t cb) {
    environ_cb = cb;
    // Example: enable any features you might need via environ_cb if desired.
}

void retro_set_video_refresh(retro_video_refresh_t cb) { video_cb = cb; }
void retro_set_audio_sample(retro_audio_sample_t cb) { audio_cb = cb; }
void retro_set_audio_sample_batch(retro_audio_sample_batch_t cb) { audio_batch_cb = cb; }
void retro_set_input_poll(retro_input_poll_t cb) { input_poll_cb = cb; }
void retro_set_input_state(retro_input_state_t cb) { input_state_cb = cb; }

void retro_reset(void) {
    if (core.rom) {
        core_unload_state(&core);
        core_init_state(&core, core.mode);
        core_load_rom(&core, core.rom, core.rom_size);
        if (core.mode == MODE_GBA) gba_cpu_reset(&core);
        else gb_cpu_reset(&core);
    }
}

// ----------------- System Info -----------------
void retro_get_system_info(struct retro_system_info *info) {
    memset(info, 0, sizeof(*info));
    info->library_name     = "Gameboy Perfect Core";
    info->library_version  = "0.1";
    info->valid_extensions = "gb|gbc|gba";
    info->need_fullpath    = false;
    info->block_extract    = false;
}

void retro_get_system_av_info(struct retro_system_av_info *info) {
    memset(info, 0, sizeof(*info));
    unsigned width = (core.mode == MODE_GBA) ? GBA_WIDTH : GB_WIDTH;
    unsigned height = (core.mode == MODE_GBA) ? GBA_HEIGHT : GB_HEIGHT;

    info->geometry.base_width  = width;
    info->geometry.base_height = height;
    info->geometry.max_width   = width;
    info->geometry.max_height  = height;
    info->geometry.aspect_ratio = (float)width / (float)height;

    info->timing.fps = 59.7275;
    info->timing.sample_rate = 44100.0;
}

// ----------------- Game Loading -----------------
bool retro_load_game(const struct retro_game_info *game) {
    if (!game || !game->data || game->size == 0) return false;

    // set mode by extension (best effort)
    core.mode = MODE_UNSET;
    if (game->path) {
        const char *ext = strrchr(game->path, '.');
        if (ext) {
            if (strcasecmp(ext, ".gba") == 0) core.mode = MODE_GBA;
            else if (strcasecmp(ext, ".gbc") == 0) core.mode = MODE_GBC;
            else core.mode = MODE_GB;
        }
    }

    core_init_state(&core, core.mode);
    if (!core_load_rom(&core, game->data, game->size)) return false;

    // call CPU reset hooks
    if (core.mode == MODE_GBA) gba_cpu_reset(&core);
    else gb_cpu_reset(&core);

    // copy game_info for possible later use
    memcpy(&game_info, game, sizeof(game_info));
    return true;
}

void retro_unload_game(void) {
    core_unload_state(&core);
}

// ----------------- Input mapping helper -----------------
static uint16_t poll_gb_buttons(void) {
    if (!input_state_cb) return 0;
    // Map common libretro joypad IDs to our gb_buttons_t bits
    uint16_t bits = 0;
    // port 0, device RETRO_DEVICE_JOYPAD
    if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT)) bits |= BUTTON_RIGHT;
    if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT))  bits |= BUTTON_LEFT;
    if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP))    bits |= BUTTON_UP;
    if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN))  bits |= BUTTON_DOWN;
    if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A))     bits |= BUTTON_A;
    if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B))     bits |= BUTTON_B;
    if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_SELECT))bits |= BUTTON_SELECT;
    if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_START)) bits |= BUTTON_START;
    return bits;
}

// ----------------- Main emulation loop (one frame) -----------------
void retro_run(void) {
    // Poll inputs
    if (input_poll_cb) input_poll_cb();

    // Map inputs into core-visible state
    uint16_t gb_buttons = poll_gb_buttons();
    if (core.mode == MODE_GBA) {
        // map to 32-bit GBA input mask; basic mapping: reuse lower bits
        gba_set_input_state(&core, (uint32_t)gb_buttons);
    } else {
        gb_set_input_state(&core, gb_buttons);
    }

    // Determine cycles to run this frame
    uint64_t target = core.cycles_per_frame ? core.cycles_per_frame : cycles_per_frame_for_mode(core.mode);

    // Execute CPU/PPU/APU for the frame in small chunks
    uint64_t run = 0;
    const unsigned chunk = 4; // small chunk in cycles; emulators often use small quanta
    while (run < target) {
        unsigned executed = 0;
        if (core.mode == MODE_GBA) {
            executed = gba_cpu_exec_cycles(&core, chunk);
            gba_ppu_step(&core, executed);
            gba_sound_step(&core, executed);
        } else {
            executed = gb_cpu_exec_cycles(&core, chunk);
            gb_ppu_step(&core, executed);
            gb_apu_step(&core, executed);
        }
        // guard: if the implementation returns 0, avoid tight infinite loop
        if (executed == 0) {
            // if CPU stub returns 0, fast-forward remaining cycles
            run = target;
            break;
        }
        run += executed;
    }

    // Submit video frame
    if (video_cb && core.framebuffer) {
        // stride bytes
        size_t pitch = core.fb_width * sizeof(pixel_t);
        video_cb(core.framebuffer, (unsigned)core.fb_width, (unsigned)core.fb_height, (unsigned)pitch);
    }
}

// ----------------- Serialization / Memory (stubs) -----------------
size_t retro_serialize_size(void) { return 0; }
bool retro_serialize(void *data, size_t size) { (void)data; (void)size; return false; }
bool retro_unserialize(const void *data, size_t size) { (void)data; (void)size; return false; }

void *retro_get_memory_data(unsigned id) { (void)id; return NULL; }
size_t retro_get_memory_size(unsigned id) { (void)id; return 0; }
