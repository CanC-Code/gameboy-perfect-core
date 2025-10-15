#ifndef CORE_STATE_H
#define CORE_STATE_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* Forward declarations */
typedef struct gb_cpu_s gb_cpu_t;
typedef struct gb_ppu_s gb_ppu_t;
typedef struct gb_apu_s gb_apu_t;

typedef struct core_state_s {
    gb_cpu_t *cpu;
    gb_ppu_t *ppu;
    gb_apu_t *apu;

    uint8_t *rom;
    size_t rom_size;

    bool ime;
} core_state_t;

/* Core functions */
core_state_t* gb_core_create(void);
void gb_core_destroy(core_state_t *state);
bool gb_core_load_rom(core_state_t *core, const uint8_t *data, size_t size);
void gb_cpu_step(core_state_t *state);
void gb_ppu_get_frame(core_state_t *state, uint16_t *buffer);

#endif /* CORE_STATE_H */
