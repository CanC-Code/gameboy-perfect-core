#ifndef CORE_STATE_H
#define CORE_STATE_H

#include <stdint.h>
#include <stddef.h>
#include "cpu.h"
#include "ppu.h"
#include "apu.h"

typedef struct core_state_s {
    gb_cpu_t cpu;
    gb_ppu_t ppu;
    gb_apu_t apu;

    uint8_t* rom;
    size_t rom_size;
} core_state_t;

core_state_t* gb_core_create(void);
void gb_core_destroy(core_state_t* state);
void gb_core_init(core_state_t* state, const uint8_t* rom_data, size_t rom_size);
void gb_core_step(core_state_t* state);
int gb_core_frame_ready(core_state_t* state);

#endif
