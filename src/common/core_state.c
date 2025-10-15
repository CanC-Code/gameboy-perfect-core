#include "core_state.h"
#include "../gb/cpu.h"
#include "../gb/gb_ppu.h"
#include "../gb/gb_apu.h"
#include <string.h>

void core_state_init(core_state_t *state) {
    memset(state, 0, sizeof(core_state_t));

    cpu_reset(state);
    gb_ppu_reset(&state->ppu);
    gb_apu_reset(&state->apu);

    state->mode = MODE_UNSET;
}

void core_load_rom(core_state_t *state, const uint8_t *data, size_t size) {
    if (size > sizeof(state->rom)) size = sizeof(state->rom);
    memcpy(state->rom, data, size);
}
