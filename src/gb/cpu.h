#ifndef GB_CPU_H
#define GB_CPU_H

#include "../common/core_state.h"
#include "mmu.h"
#include <stdint.h>
#include <stdbool.h>

/* CPU registers */
typedef struct {
    union { struct { uint8_t f; uint8_t a; }; uint16_t af; };
    union { struct { uint8_t c; uint8_t b; }; uint16_t bc; };
    union { struct { uint8_t e; uint8_t d; }; uint16_t de; };
    union { struct { uint8_t l; uint8_t h; }; uint16_t hl; };

    uint16_t sp; /* Stack pointer */
    uint16_t pc; /* Program counter */

    bool ime; /* Interrupt Master Enable */
    uint8_t halted;
} gb_cpu_t;

/* Initialize CPU state */
void gb_cpu_init(core_state_t *cs);

/* Reset CPU to power-on state */
void gb_cpu_reset(core_state_t *cs);

/* Execute N cycles */
void gb_cpu_step(core_state_t *cs, int cycles);

/* Run until next VBlank (frame) */
void gb_cpu_run_frame(core_state_t *cs);

#endif /* GB_CPU_H */
