#include "libretro.h"
#include "gb/cpu.h"
#include "gb/mmu.h"
#include "gb/ppu.h"
#include "gb/gb_apu.h"

// GB Core state
static gb_cpu_t gb_cpu;
static gb_mmu_t gb_mmu;
static gb_ppu_t gb_ppu;
static gb_apu_t gb_apu;

// Retro callback placeholders
retro_environment_t environ_cb;
void (*video_cb)(const void *data, unsigned width, unsigned height, size_t pitch);
size_t (*audio_batch_cb)(const int16_t *data, size_t frames);

bool retro_load_game(const void *info)
{
    gb_mmu_init(&gb_mmu);
    gb_cpu_init(&gb_cpu, gb_mmu.mem);
    gb_ppu_init(&gb_ppu);
    gb_apu_init(&gb_apu);
    return true;
}

bool retro_serialize(void *data_, size_t size) { return false; }
bool retro_unserialize(const void *data_, size_t size) { return false; }
void retro_reset(void) { gb_cpu_reset(&gb_cpu); }

void retro_get_system_av_info(void)
{
    struct retro_game_geometry geom = {160, 144, 160, 144, 0.0f};
    (void)geom;
}

void retro_run(void)
{
    gb_cpu_step(&gb_cpu, 69905 / 60);
    gb_ppu_step(&gb_ppu, &gb_cpu);
    gb_apu_step(&gb_apu, 69905 / 60);

    audio_batch_cb(gb_apu.buffer, gb_apu.buffer_pos);
    gb_apu.buffer_pos = 0;
}

bool retro_load_game_special(unsigned type, const struct retro_game_info *info, size_t num) { return false; }
void retro_cheat_set(unsigned index, bool enabled, const char *code) {}
