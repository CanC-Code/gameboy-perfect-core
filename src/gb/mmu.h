#ifndef GB_MMU_H
#define GB_MMU_H

#include "../common/core_state.h"
#include <stdint.h>
#include <stdbool.h>

/* MMU public API for GB/GBC cores */

/* Initialize MMU memory map for a core */
void gb_mmu_init(core_state_t *cs);

/* Read / write helpers (CPU calls these) */
uint8_t mmu_read8(core_state_t *cs, uint16_t addr);
void mmu_write8(core_state_t *cs, uint16_t addr, uint8_t value);
uint16_t mmu_read16(core_state_t *cs, uint16_t addr);

/* Optional: load ROM into MMU */
bool gb_mmu_load_rom(core_state_t *cs, const void *data, size_t size);

/* Reset MMU state (power-on) */
void gb_mmu_reset(core_state_t *cs);

#endif /* GB_MMU_H */
