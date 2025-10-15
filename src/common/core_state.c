#include "core_state.h"
#include "cpu.h"
#include "ppu.h"
#include "apu.h"
#include <stdlib.h>
#include <string.h>

/* Initialize core state */
core_state_t* gb_core_create(void) {
    core_state_t *state = (core_state_t*)malloc(sizeof(core_state_t));
    if (!state) return NULL;

    memset(state, 0, sizeof(core_state_t));

    state->cpu = (gb_cpu_t*)malloc(sizeof(gb_cpu_t));
    state->ppu = (gb_ppu_t*)malloc(sizeof(gb_ppu_t));
    state->apu = (gb_apu_t*)malloc(sizeof(gb_apu_t));

    if (!state->cpu || !state->ppu || !state->apu) {
        gb_core_destroy(state);
        return NULL;
    }

    /* Initialize CPU registers */
    state->cpu->af = 0x01B0;
    state->cpu->bc = 0x0013;
    state->cpu->de = 0x00D8;
    state->cpu->hl = 0x014D;
    state->cpu->sp = 0xFFFE;
    state->cpu->pc = 0x0100;

    state->ime = true;

    gb_ppu_reset(state->ppu);
    gb_apu_reset(state->apu);

    return state;
}

/* Free core state */
void gb_core_destroy(core_state_t *state) {
    if (!state) return;
    if (state->cpu) free(state->cpu);
    if (state->ppu) free(state->ppu);
    if (state->apu) free(state->apu);
    if (state->rom) free(state->rom);
    free(state);
}

/* Load ROM */
bool gb_core_load_rom(core_state_t *core, const uint8_t *data, size_t size) {
    if (!core || !data || !size) return false;
    core->rom = (uint8_t*)malloc(size);
    if (!core->rom) return false;
    memcpy(core->rom, data, size);
    core->rom_size = size;
    return true;
}

/* CPU step stub */
void gb_cpu_step(core_state_t *state) {
    if (!state || !state->cpu || !state->rom) return;

    uint8_t opcode = state->rom[state->cpu->pc];
    (void)opcode; // placeholder
    state->cpu->pc++;

    gb_ppu_step(state->ppu);
    gb_apu_step(state->apu);
}

/* Get framebuffer */
void gb_ppu_get_frame(core_state_t *state, uint16_t *buffer) {
    if (!state || !buffer) return;
    memcpy(buffer, state->ppu->framebuffer, 160*144*sizeof(uint16_t));
}
