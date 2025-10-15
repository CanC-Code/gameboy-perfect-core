#include "core_state.h"
#include "../gb/cpu.h"
#include "../gb/mmu.h"
#include "../gb/ppu.h"
#include "../gb/gb_apu.h"
#include <string.h>

void core_state_init(core_state_t *state) {
    if (!state) return;

    memset(state, 0, sizeof(core_state_t));

    // Initialize each subsystem
    gb_cpu_reset(&state->cpu);
    gb_mmu_reset(&state->mmu);
    gb_apu_reset(&state->apu);
    gb_ppu_reset(&state->ppu);
}
