#include "cpu.h"
#include "../common/core_state.h"
#include "mmu.h"
#include "ppu.h"
#include "gb_apu.h"
#include <stdbool.h>
#include <stdint.h>

// Reset CPU registers and flags
void gb_cpu_reset(gb_cpu_t *cpu) {
    cpu->reg.af = 0x01B0;
    cpu->reg.bc = 0x0013;
    cpu->reg.de = 0x00D8;
    cpu->reg.hl = 0x014D;
    cpu->reg.sp = 0xFFFE;
    cpu->reg.pc = 0x0100;
    cpu->ime = true;
    cpu->halted = false;
}

// Fetch next byte from memory
static uint8_t fetch_byte(core_state_t *state) {
    uint8_t val = gb_mmu_read_byte(&state->mmu, state->cpu.reg.pc);
    state->cpu.reg.pc++;
    return val;
}

// Fetch next word (2 bytes) from memory
static uint16_t fetch_word(core_state_t *state) {
    uint8_t low = fetch_byte(state);
    uint8_t high = fetch_byte(state);
    return (high << 8) | low;
}

// Step CPU one instruction
void gb_cpu_step(core_state_t *state) {
    uint8_t opcode = fetch_byte(state);

    switch (opcode) {
        case 0x00: /* NOP */
            break;

        case 0xAF: /* XOR A */
            state->cpu.reg.af ^= state->cpu.reg.af;
            // Clear flags after XOR A
            state->cpu.reg.f = 0x80;
            break;

        default:
            // Unimplemented opcode
            // For now, just ignore or log
            break;
    }

    // Advance PPU and APU cycles
    gb_ppu_tick(&state->ppu);
    gb_apu_tick(&state->apu);
}
