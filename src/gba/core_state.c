#include "cpu.h"
#include "core_state.h"
#include <stdlib.h>
#include <string.h>

bool gba_core_init(gba_core_t *core) {
    if (!core) return false;
    core->mode = MODE_GBA;
    core->rom = NULL;
    core->rom_size = 0;
    core->cycles = 0;
    core->rom_loaded = false;
    memset(core->ram, 0, sizeof(core->ram));
    return true;
}

void gba_core_reset(gba_core_t *core) {
    if (!core) return;
    core->cycles = 0;
    memset(core->ram, 0, sizeof(core->ram));
}

bool gba_core_load_rom(gba_core_t *core, const uint8_t *data, size_t size) {
    if (!core || !data || size == 0 || size > GBA_ROM_MAX_SIZE) return false;

    if (core->rom) free(core->rom);
    core->rom = (uint8_t *)malloc(size);
    if (!core->rom) return false;

    memcpy(core->rom, data, size);
    core->rom_size = size;
    core->rom_loaded = true;
    return true;
}

void gba_core_unload_rom(gba_core_t *core) {
    if (!core) return;
    if (core->rom) {
        free(core->rom);
        core->rom = NULL;
    }
    core->rom_size = 0;
    core->rom_loaded = false;
    memset(core->ram, 0, sizeof(core->ram));
    core->cycles = 0;
}
