#ifndef GBA_CORE_STATE_H
#define GBA_CORE_STATE_H

#include <stdint.h>
#include <stdbool.h>
#include "core_common.h"

// GBA memory layout
#define GBA_RAM_SIZE       0x00040000
#define GBA_ROM_MAX_SIZE   0x02000000

typedef struct {
    core_mode_t mode;      // CORE_GBA
    uint8_t *rom;
    size_t rom_size;
    uint8_t ram[GBA_RAM_SIZE];
    uint64_t cycles;
    bool rom_loaded;
} gba_core_t;

// Core management
bool gba_core_init(gba_core_t *core);
void gba_core_reset(gba_core_t *core);
bool gba_core_load_rom(gba_core_t *core, const uint8_t *data, size_t size);
void gba_core_unload_rom(gba_core_t *core);

#endif // GBA_CORE_STATE_H
