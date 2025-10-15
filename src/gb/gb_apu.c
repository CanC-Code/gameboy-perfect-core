#include "gb_apu.h"
#include <string.h>

// Minimalistic square wave example
typedef struct {
    uint16_t phase;
    uint16_t period;
    uint8_t duty;
    uint8_t volume;
} gb_channel_t;

static gb_channel_t ch1, ch2, ch3, ch4;

void gb_apu_init(gb_apu_t *apu) {
    memset(apu, 0, sizeof(gb_apu_t));
    gb_apu_reset(apu);
}

void gb_apu_reset(gb_apu_t *apu) {
    memset(&ch1, 0, sizeof(ch1));
    memset(&ch2, 0, sizeof(ch2));
    memset(&ch3, 0, sizeof(ch3));
    memset(&ch4, 0, sizeof(ch4));
    apu->sample_count = 0;
}

// Step one CPU cycle
void gb_apu_step(gb_apu_t *apu, uint16_t cycles) {
    for (uint16_t i = 0; i < cycles; i++) {
        // Simple square wave synthesis for demonstration
        int16_t sample = 0;

        // Channel 1
        ch1.phase += 1;
        if (ch1.phase >= ch1.period) ch1.phase = 0;
        sample += ((ch1.phase * 8 / ch1.period) < ch1.duty ? ch1.volume : -ch1.volume);

        // Channel 2
        ch2.phase += 1;
        if (ch2.phase >= ch2.period) ch2.phase = 0;
        sample += ((ch2.phase * 8 / ch2.period) < ch2.duty ? ch2.volume : -ch2.volume);

        // Channel 3 (wave)
        ch3.phase += 1;
        if (ch3.phase >= ch3.period) ch3.phase = 0;
        sample += ((ch3.phase * 8 / ch3.period) < ch3.duty ? ch3.volume : -ch3.volume);

        // Channel 4 (noise)
        ch4.phase += 1;
        if (ch4.phase >= ch4.period) ch4.phase = 0;
        sample += ((ch4.phase * 8 / ch4.period) < ch4.duty ? ch4.volume : -ch4.volume);

        // Push to buffer
        if (apu->sample_count < AUDIO_BUFFER_SIZE) {
            apu->sample_buffer[apu->sample_count++] = sample;
        } else {
            apu->sample_count = 0; // reset to avoid overflow
        }
    }
}
