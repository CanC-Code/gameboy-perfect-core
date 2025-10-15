#include "core_state.h"
#include "cpu.h"
#include "ppu.h"
#include "apu.h"
#include "mmu.h"
#include <stdlib.h>
#include <string.h>

void gb_core_init(core_state_t *state) {
    if (!state) return;

    state->mmu = (gb_mmu_t *)malloc(sizeof(gb_mmu_t));
    if (!state->mmu) return;

    gb_mmu_reset(state->mmu);
    gb_cpu_reset(&state->cpu);
    gb_ppu_reset(&state->ppu);
    gb_apu_reset(&state->apu);
}

void gb_core_step(core_state_t *state) {
    if (!state) return;

    // Execute one CPU instruction
    gb_cpu_step(&state->cpu, state);
}

void gb_core_destroy(core_state_t *state) {
    if (!state) return;
    if (state->mmu) {
        free(state->mmu);
        state->mmu = NULL;
    }
}
