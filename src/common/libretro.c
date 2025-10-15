#include "libretro.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/* Core headers */
#include "cpu.h"
#include "ppu.h"
#include "apu.h"
#include "mmu.h"
#include "core_state.h"

/* Opaque core pointer */
static core_state_t *gb_core = NULL;

/* RetroArch callbacks */
static retro_video_refresh_t       video_cb       = (retro_video_refresh_t)NULL;
static retro_audio_sample_batch_t  audio_batch_cb = (retro_audio_sample_batch_t)NULL;
static retro_input_poll_t          input_poll_cb  = (retro_input_poll_t)NULL;
static retro_input_state_t         input_state_cb = (retro_input_state_t)NULL;

/* Video buffer */
static uint16_t frame_buffer[160 * 144];

/* Audio buffer */
#define AUDIO_BUFFER_SIZE 2048
static int16_t audio_buffer[AUDIO_BUFFER_SIZE];
static size_t audio_buffer_len = 0;

/* Callbacks setup */
void retro_set_video_refresh(retro_video_refresh_t cb)       { video_cb = cb; }
void retro_set_audio_sample_batch(retro_audio_sample_batch_t cb) { audio_batch_cb = cb; }
void retro_set_input_poll(retro_input_poll_t cb)            { input_poll_cb = cb; }
void retro_set_input_state(retro_input_state_t cb)          { input_state_cb = cb; }
void retro_set_environment(retro_environment_t cb)          { (void)cb; }

/* System info */
void retro_get_system_info(struct retro_system_info *info) {
    info->library_name     = "Gameboy Perfect Core";
    info->library_version  = "0.1";
    info->valid_extensions = "gb|gbc|gba";
    info->need_fullpath    = false;
    info->block_extract    = false;
}

void retro_get_system_av_info(struct retro_system_av_info *info) {
    info->timing.fps         = 60.0;
    info->timing.sample_rate = 44100.0;
    info->geometry.base_width  = 160;
    info->geometry.base_height = 144;
    info->geometry.max_width   = 160;
    info->geometry.max_height  = 144;
    info->geometry.aspect_ratio = 160.0 / 144.0;
}

/* Core management */
bool retro_load_game(const struct retro_game_info *game) {
    if (!game || !game->data || !game->size)
        return false;

    gb_core = gb_core_create();
    if (!gb_core)
        return false;

    gb_core_load_rom(gb_core, game->data, game->size);
    return true;
}

void retro_unload_game(void) {
    if (gb_core) {
        gb_core_destroy(gb_core);
        gb_core = NULL;
    }
}

size_t retro_serialize_size(void) { return 0; }
bool retro_serialize(void *data_, size_t size) { (void)data_; (void)size; return false; }
bool retro_unserialize(const void *data_, size_t size) { (void)data_; (void)size; return false; }

/* Cheat stub */
void retro_cheat_set(unsigned index, bool enabled, const char *code) {
    (void)index; (void)enabled; (void)code;
}

/* Run one frame */
void retro_run(void) {
    if (!gb_core) return;

    if (input_poll_cb)
        input_poll_cb();

    /* TODO: Map inputs */

    gb_cpu_step(gb_core);
    gb_ppu_step(gb_core);

    gb_ppu_get_frame(gb_core, frame_buffer);

    if (video_cb)
        video_cb(frame_buffer, 160, 144, 160 * sizeof(uint16_t));

    audio_buffer_len = AUDIO_BUFFER_SIZE;
    gb_apu_step(gb_core, audio_buffer, &audio_buffer_len);

    if (audio_batch_cb && audio_buffer_len)
        audio_batch_cb(audio_buffer, audio_buffer_len);
}

bool retro_load_game_special(unsigned type, const struct retro_game_info *info, size_t num) {
    (void)type; (void)info; (void)num;
    return false;
}

unsigned retro_get_region(void) { return RETRO_REGION_NTSC; }
