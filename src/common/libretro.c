#include <libretro.h>
#include <stdlib.h>
#include <string.h>
#include "core_state.h"

// Core state
static core_state_t* state = NULL;

// Libretro callbacks
static retro_video_refresh_t video_cb;
static retro_audio_sample_t audio_cb;
static retro_input_poll_t input_poll_cb;
static retro_input_state_t input_state_cb;

// Video buffer
static uint16_t video_buffer[160 * 144];

// Audio buffer (placeholder)
#define AUDIO_BUFFER_SIZE 2048
static int16_t audio_buffer[AUDIO_BUFFER_SIZE];
static size_t audio_index = 0;

// --- Libretro API functions ---

void retro_init(void) {
    state = gb_core_create();
}

void retro_deinit(void) {
    if (state) {
        gb_core_destroy(state);
        state = NULL;
    }
}

unsigned retro_api_version(void) {
    return RETRO_API_VERSION;
}

void retro_set_environment(retro_environment_t cb) {
    (void)cb;
}

void retro_set_video_refresh(retro_video_refresh_t cb) {
    video_cb = cb;
}

void retro_set_audio_sample(retro_audio_sample_t cb) {
    audio_cb = cb;
}

void retro_set_audio_sample_batch(retro_audio_sample_batch_t cb) {
    (void)cb; // not used, simple implementation
}

void retro_set_input_poll(retro_input_poll_t cb) {
    input_poll_cb = cb;
}

void retro_set_input_state(retro_input_state_t cb) {
    input_state_cb = cb;
}

void retro_reset(void) {
    if (state) {
        gb_cpu_reset(&state->cpu);
        gb_ppu_reset(&state->ppu);
        gb_apu_reset(&state->apu);
    }
}

// Load a ROM
bool retro_load_game(const struct retro_game_info *info) {
    if (!info || !info->data || !info->size) return false;

    gb_core_init(state, (const uint8_t*)info->data, info->size);
    return true;
}

void retro_unload_game(void) {
    // Free ROM data
    if (state && state->rom) {
        free(state->rom);
        state->rom = NULL;
        state->rom_size = 0;
    }
}

// Main run loop
void retro_run(void) {
    if (!state) return;

    input_poll_cb();

    // Step CPU, PPU, APU until a frame is ready
    do {
        int cycles = gb_cpu_step(&state->cpu, state);
        gb_ppu_step(&state->ppu, cycles);
        gb_apu_step(&state->apu, cycles);
    } while (!gb_core_frame_ready(state));

    // Video callback
    video_cb(state->ppu.framebuffer, 160, 144, 160 * sizeof(uint16_t));

    // Audio callback placeholder
    audio_cb(0, 0);
}

size_t retro_serialize_size(void) {
    return 0; // Not implemented
}

bool retro_serialize(void *data, size_t size) {
    return false;
}

bool retro_unserialize(const void *data, size_t size) {
    return false;
}

void retro_cheat_reset(void) {}
void retro_cheat_set(unsigned index, bool enabled, const char *code) {}
void retro_get_system_info(struct retro_system_info *info) {
    memset(info, 0, sizeof(*info));
    info->library_name = "GameBoy Perfect Core";
    info->library_version = "1.0";
    info->valid_extensions = "gb|gbc";
    info->need_fullpath = false;
    info->block_extract = false;
}

void retro_get_system_av_info(struct retro_system_av_info *info) {
    info->timing.fps = 59.73;
    info->timing.sample_rate = 44100.0;
    info->geometry.base_width = 160;
    info->geometry.base_height = 144;
    info->geometry.max_width = 160;
    info->geometry.max_height = 144;
    info->geometry.aspect_ratio = 160.0 / 144.0;
}
