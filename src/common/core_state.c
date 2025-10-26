#include "core_state.h"
#include <string.h>

void gb_core_init(core_state_t* state, const uint8_t* rom_data, size_t rom_size) {
    memset(state, 0, sizeof(core_state_t));

    state->rom = rom_data;
    state->rom_size = rom_size;
    state->mmu = (gb_mmu_t*)malloc(sizeof(gb_mmu_t));
    if (!state->mmu) return;

    gb_mmu_reset(state->mmu);
    gb_cpu_init(&state->cpu);
    gb_ppu_init(&state->ppu);
    gb_apu_init(&state->apu);

    state->running = true;
}

void gb_core_reset(core_state_t* state) {
    gb_cpu_reset(&state->cpu);
    gb_ppu_reset(&state->ppu);
    gb_apu_reset(&state->apu);
    gb_mmu_reset(state->mmu);
}

void gb_core_step(core_state_t* state, int cycles) {
    gb_cpu_step(&state->cpu, state->mmu, cycles);
    gb_ppu_step(&state->ppu, cycles);
    gb_apu_step(&state->apu, cycles);
}

void gb_core_destroy(core_state_t* state) {
    if (state->mmu) {
        free(state->mmu);
        state->mmu = NULL;
    }
    state->running = false;
}
