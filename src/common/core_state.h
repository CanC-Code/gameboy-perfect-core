#ifndef CORE_STATE_H
#define CORE_STATE_H

#include "../gb/cpu.h"
#include "../gb/mmu.h"
#include "../gb/ppu.h"
#include "../gb/gb_apu.h"

// Represents the full emulator system state
typedef struct core_state_s {
    gb_cpu_t cpu;
    gb_mmu_t mmu;
    gb_ppu_t ppu;
    gb_apu_t apu;
} core_state_t;

// Initializes the emulator subsystems
void core_state_init(core_state_t *state);

#endif // CORE_STATE_H
