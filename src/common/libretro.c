#include "libretro.h"
#include "core_state.h"
#include "../gb/cpu.h"
#include "../gb/gb_ppu.h"
#include "../gb/gb_apu.h"
#include <stdint.h>
#include <string.h>

static core_state_t core;
static retro_video_refresh_t video_cb;
static retro_audio_sample_t audio_cb;
static retro_input_state_t input_cb;

void retro_set_video_refresh(retro_video_refresh_t cb) { video_cb = cb; }
void retro_set_audio_sample(retro_audio_sample_t cb) { audio_cb = cb; }
void retro_set_input_state(retro_input_state_t cb) { input_cb = cb; }

void retro_init(void) { core_state_init(&core); }
void retro_deinit(void) {}

unsigned retro_api_version(void) { return RETRO_API_VERSION; }

void retro_get_system_info(struct retro_system_info *info) {
    memset(info, 0, sizeof(*info));
    info->library_name = "GameBoy Perfect Core";
    info->library_version = "0.1";
    info->need_fullpath = true;
    info->valid_extensions = "gb|gbc|gba";
}

void retro_get_system_av_info(struct retro_system_av_info *info) {
    struct retro_game_geometry geom = {160, 144, 160, 144};
    struct retro_system_timing timing = {59.73, 44100.0};
    info->geometry = geom;
    info->timing = timing;
}

void retro_reset(void) {
    core_state_init(&core);
}

void retro_run(void) {
    cpu_step(&core);

    // Send video
    video_cb(core.ppu.framebuffer, 160, 144, 160 * sizeof(uint32_t));

    // Send audio (dummy for now)
    for (int i = 0; i < 4; i++) {
        audio_cb(0, 0);
    }
}

size_t retro_serialize_size(void) { return sizeof(core_state_t); }

bool retro_serialize(void *data, size_t size) {
    if (size != sizeof(core_state_t)) return false;
    memcpy(data, &core, sizeof(core_state_t));
    return true;
}

bool retro_unserialize(const void *data, size_t size) {
    if (size != sizeof(core_state_t)) return false;
    memcpy(&core, data, sizeof(core_state_t));
    return true;
}

void retro_cheat_reset(void) {}
void retro_cheat_set(unsigned index, bool enabled, const char *code) {}

void retro_set_controller_port_device(unsigned port, unsigned device) {}

bool retro_load_game(const struct retro_game_info *game) {
    core_state_init(&core);
    core_load_rom(&core, (const uint8_t *)game->data, game->size);

    if (game->size > 0x8000) core.mode = MODE_GBC;
    else core.mode = MODE_GB;

    return true;
}

void retro_unload_game(void) {}
