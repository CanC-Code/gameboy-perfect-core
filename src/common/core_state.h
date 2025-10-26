#ifndef GB_CORE_STATE_H
#define GB_CORE_STATE_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mmu.h"
#include "cpu.h"
#include "ppu.h"
#include "apu.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct core_state_s {
    gb_cpu_t cpu;
    gb_ppu_t ppu;
    gb_apu_t apu;
    gb_mmu_t *mmu;        // dynamically allocated MMU
    const uint8_t *rom;   // pointer to loaded ROM data
    size_t rom_size;
    bool running;
} core_state_t;

void gb_core_init(core_state_t* state, const uint8_t* rom_data, size_t rom_size);
void gb_core_reset(core_state_t* state);
void gb_core_step(core_state_t* state, int cycles);
void gb_core_destroy(core_state_t* state);

#ifdef __cplusplus
}
#endif

#endif /* GB_CORE_STATE_H */
