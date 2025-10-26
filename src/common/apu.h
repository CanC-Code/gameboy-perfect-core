#ifndef GB_APU_H
#define GB_APU_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define GB_APU_SAMPLE_RATE 44100

typedef struct {
    // Channel enable flags
    bool ch1_enabled;
    bool ch2_enabled;
    bool ch3_enabled;
    bool ch4_enabled;

    // Sound registers
    uint8_t ch1_regs[5];
    uint8_t ch2_regs[5];
    uint8_t ch3_regs[5];
    uint8_t ch4_regs[5];

    // Internal counters and phase accumulators
    double ch1_phase;
    double ch2_phase;
    double ch3_phase;
    double ch4_phase;

    // Noise generator state
    uint16_t noise_lfsr;

    // Master volume control
    float volume;

    // Frame sequencer counter
    uint32_t frame_seq;
    uint32_t cycles_per_sample;
    uint32_t cycle_counter;

    // Output mix buffer (mono or stereo)
    float left;
    float right;

} gb_apu_t;

// --- Public API ---
void gb_apu_init(gb_apu_t *apu);
void gb_apu_reset(gb_apu_t *apu);
void gb_apu_step(gb_apu_t *apu, int cycles);
float gb_apu_sample_left(gb_apu_t *apu);
float gb_apu_sample_right(gb_apu_t *apu);

#ifdef __cplusplus
}
#endif

#endif /* GB_APU_H */
