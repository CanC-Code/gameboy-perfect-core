#ifndef MMU_H
#define MMU_H

#include <stdint.h>
#include <stddef.h>
#include "core_common.h"

void mmu_init(core_mode_t mode, const uint8_t *rom, size_t rom_size);
uint8_t mmu_read8(uint32_t addr);
void mmu_write8(uint32_t addr, uint8_t val);

// For convenience in CPU stubs
const uint8_t* mmu_get_rom_ptr(void);
size_t mmu_get_rom_size(void);

#endif // MMU_H
