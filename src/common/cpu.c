#include <stdint.h>
#include <stdbool.h>
#include "core_state.h"

// Reset CPU state
void cpu_reset(core_state_t *state, uint8_t *rom)
{
    state->reg.af = 0x01B0;
    state->reg.bc = 0x0013;
    state->reg.de = 0x00D8;
    state->reg.hl = 0x014D;
    state->reg.sp = 0xFFFE;
    state->reg.pc = 0x0100;
    state->ime = true;
    state->rom = rom;
}

// Fetch a single byte from ROM and advance PC
static uint8_t fetch_byte(core_state_t *state)
{
    uint8_t val = state->rom[state->reg.pc];
    state->reg.pc++;
    return val;
}

// Fetch two bytes from ROM and advance PC
static uint16_t fetch_word(core_state_t *state)
{
    uint16_t low = fetch_byte(state);
    uint16_t high = fetch_byte(state);
    return (high << 8) | low;
}

// CPU step ? simplified example (implement your instructions here)
void cpu_step(core_state_t *state, int cycles)
{
    for (int i = 0; i < cycles; i++)
    {
        uint8_t opcode = fetch_byte(state);

        switch (opcode)
        {
            case 0x00: // NOP
                break;

            case 0xAF: // XOR A
                state->reg.af ^= state->reg.af;
                break;

            default:
                // Unknown opcode ? just NOP for now
                break;
        }

        // Tick PPU and APU
        ppu_tick(&state->ppu);
        gb_apu_tick(&state->apu);
    }
}

// Placeholder functions for missing PPU/APU ticks
void ppu_tick(gb_ppu_t *ppu)
{
    // TODO: implement proper PPU stepping
    (void)ppu;
}

void gb_apu_tick(gb_apu_t *apu)
{
    // TODO: implement proper APU stepping
    (void)apu;
}
