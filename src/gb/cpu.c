#include "cpu.h"
#include "core_state.h"
#include "ppu.h"
#include "gb_apu.h"

#include <stdint.h>
#include <stdbool.h>

void cpu_reset(core_state_t *state) {
    state->reg.af = 0x01B0;
    state->reg.bc = 0x0013;
    state->reg.de = 0x00D8;
    state->reg.hl = 0x014D;
    state->reg.sp = 0xFFFE;
    state->reg.pc = 0x0100;
    state->ime = true;
}

static uint8_t fetch_byte(core_state_t *state) {
    uint8_t val = state->rom[state->reg.pc];
    state->reg.pc++;
    return val;
}

static uint16_t fetch_word(core_state_t *state) {
    uint16_t low = fetch_byte(state);
    uint16_t high = fetch_byte(state);
    return (high << 8) | low;
}

void cpu_step(core_state_t *state) {
    uint8_t opcode = fetch_byte(state);
    // Simple skeleton: implement common opcodes
    switch (opcode) {
        case 0x00: /* NOP */ break;
        case 0xAF: /* XOR A */ state->reg.af ^= state->reg.af; break;
        // Add all GB CPU opcodes here
        default: break;
    }

    // Advance PPU and APU each CPU cycle
    ppu_tick(&state->ppu);
    gb_apu_tick(&state->apu);
}
