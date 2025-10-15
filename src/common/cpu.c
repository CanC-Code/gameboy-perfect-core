#include "cpu.h"
#include "core_state.h"
#include "ppu.h"
#include "apu.h"

void gb_cpu_step(core_state_t *state) {
    if (!state || !state->cpu || !state->rom) return;

    uint8_t opcode = state->rom[state->cpu->pc];
    (void)opcode;
    state->cpu->pc++;

    gb_ppu_step(state->ppu);
    gb_apu_step(state->apu);
}
