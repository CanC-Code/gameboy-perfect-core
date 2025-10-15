#include "gb_mem.h"
#include <string.h>

void gb_mem_init(gb_mem_t *mem) {
    if (!mem) return;
    memset(mem, 0, sizeof(gb_mem_t));
}

void gb_mem_reset(gb_mem_t *mem) {
    if (!mem) return;
    memset(mem, 0, sizeof(gb_mem_t));
}

uint8_t gb_mem_read(gb_mem_t *mem, uint16_t addr) {
    (void)mem;
    (void)addr;
    return 0xFF; // placeholder value
}

void gb_mem_write(gb_mem_t *mem, uint16_t addr, uint8_t value) {
    (void)mem;
    (void)addr;
    (void)value;
}
