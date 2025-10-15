#ifndef CORE_STATE_H
#define CORE_STATE_H

#include "core_common.h"
#include "../gb/gb_ppu.h"
#include "../gb/gb_apu.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    // CPU registers
    union {
        struct { uint8_t f, a, c, b, e, d, l, h; };
        struct { uint16_t af, bc, de, hl; };
    } reg;
    uint16_t sp;
    uint16_t pc;
    bool ime; // interrupt master enable

    core_mode_t mode;
    gb_ppu_t ppu;
    gb_apu_t apu;

    uint8_t rom[0x100000]; // max 1MB ROM
} core_state_t;

void core_state_init(core_state_t *state);
void core_load_rom(core_state_t *state, const uint8_t *data, size_t size);

#endif // CORE_STATE_H
