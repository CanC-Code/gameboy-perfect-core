#include "libretro.h"
#include "core_common.h"
#include "../gb/cpu.h"
#include "../gb/ppu.h"
#include "../gb/apu.h"

// RetroArch callbacks
static retro_video_refresh_t video_cb;
static retro_audio_sample_t audio_cb;
static retro_audio_sample_batch_t audio_batch_cb;
static retro_environment_t environ_cb;
static retro_input_state_t input_state_cb;
static retro_input_poll_t input_poll_cb;

// Core state
static core_mode_t core_mode;
static gb_cpu_t cpu;
static gb_ppu_t ppu;
static gb_apu_t apu;
static bool initialized = false;

// Video buffer
static pixel_t video_buffer[GB_HEIGHT][GB_WIDTH];

// Frame sync
static void retro_run_frame(void) {
    input_poll_cb();

    // Step CPU
    gb_cpu_step(&cpu);

    // Step PPU
    gb_ppu_step(&ppu, cpu.cycles);

    // Step APU
    gb_apu_step(&apu, cpu.cycles);

    // Generate audio
    int16_t audio_buffer[512];
    gb_apu_generate_samples(&apu, audio_buffer, 512);
    audio_batch_cb(audio_buffer, 512);

    // Render frame
    video_cb((const void*)video_buffer, GB_WIDTH, GB_HEIGHT, GB_WIDTH * sizeof(pixel_t));
}

// --- Core functions ---
void retro_init(void) {
    initialized = true;
    gb_cpu_init(&cpu);
    gb_ppu_init(&ppu);
    gb_apu_init(&apu);
}

void retro_deinit(void) {
    initialized = false;
}

unsigned retro_api_version(void) { return RETRO_API_VERSION; }

void retro_set_environment(retro_environment_t cb) {
    environ_cb = cb;

    // Set pixel format
    enum retro_pixel_format fmt = RETRO_PIXEL_FORMAT_XRGB8888;
    environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &fmt);
}

void retro_set_video_refresh(retro_video_refresh_t cb) { video_cb = cb; }
void retro_set_audio_sample(retro_audio_sample_t cb) { audio_cb = cb; }
void retro_set_audio_sample_batch(retro_audio_sample_batch_t cb) { audio_batch_cb = cb; }
void retro_set_input_poll(retro_input_poll_t cb) { input_poll_cb = cb; }
void retro_set_input_state(retro_input_state_t cb) { input_state_cb = cb; }

void retro_reset(void) {
    gb_cpu_reset(&cpu);
    gb_ppu_reset(&ppu);
    gb_apu_reset(&apu);
}

// ROM loading
bool retro_load_game(const struct retro_game_info *info) {
    if (!info || !info->data || !info->size) return false;

    // Detect mode
    if (info->size > 0x10000) core_mode = MODE_GBC;
    else core_mode = MODE_GB;

    // Load ROM into CPU memory
    gb_cpu_load_rom(&cpu, info->data, info->size);

    retro_reset();
    return true;
}

void retro_unload_game(void) { retro_reset(); }

unsigned retro_get_region(void) { return RETRO_REGION_NTSC; }

size_t retro_serialize_size(void) { return gb_cpu_save_size(&cpu); }

bool retro_serialize(void *data, size_t size) {
    return gb_cpu_save_state(&cpu, data, size);
}

bool retro_unserialize(const void *data, size_t size) {
    return gb_cpu_load_state(&cpu, data, size);
}

void *retro_get_memory_data(unsigned id) {
    if (id == RETRO_MEMORY_SYSTEM_RAM) return cpu.ram;
    return NULL;
}

size_t retro_get_memory_size(unsigned id) {
    if (id == RETRO_MEMORY_SYSTEM_RAM) return sizeof(cpu.ram);
    return 0;
}

void retro_run(void) {
    retro_run_frame();
}

unsigned retro_get_input_bitmasks(void) { return 0; }
