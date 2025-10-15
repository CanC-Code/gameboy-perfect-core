#include "core_common.h"
#include "core_state.h"
#include "../gb/audio_stub.h"
#include "libretro.h"
#include <stdint.h>
#include <stdlib.h>

extern retro_audio_sample_batch_t audio_batch_cb;
static struct gb_apu_t gb_apu;

// Initialize APU
void audio_init(void) {
    gb_apu_init(&gb_apu);
}

// Generate one frame of audio and send to RetroArch
void audio_run(void) {
    if (!audio_batch_cb) return;

    const size_t samples_per_frame = 735; // 44100Hz / 59.7fps
    int16_t buffer[samples_per_frame * 2]; // stereo

    for (size_t i = 0; i < samples_per_frame; i++) {
        int16_t sample = gb_apu_step(&gb_apu);
        buffer[i * 2 + 0] = sample; // left
        buffer[i * 2 + 1] = sample; // right
    }

    audio_batch_cb(buffer, samples_per_frame);
}

void audio_reset(void) {
    gb_apu_reset(&gb_apu);
}

void audio_deinit(void) {
    // Nothing dynamic yet
}
