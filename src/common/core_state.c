#include "core_state.h"

void core_state_init(core_state_t *state) {
    gb_cpu_reset(&state->cpu);
    gb_mmu_reset(&state->mmu);
    gb_ppu_reset(&state->ppu);
    gb_apu_reset(&state->apu);
}
