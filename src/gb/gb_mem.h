#ifndef GB_MEM_H
#define GB_MEM_H

#include <stdint.h>
#include <stdbool.h>

typedef struct gb_mem_s {
    uint8_t wram[0x2000];  // Work RAM
    uint8_t hram[0x7F];    // High RAM
    uint8_t io[0x80];      // IO Registers
} gb_mem_t;

void gb_mem_init(gb_mem_t *mem);
void gb_mem_reset(gb_mem_t *mem);
uint8_t gb_mem_read(gb_mem_t *mem, uint16_t addr);
void gb_mem_write(gb_mem_t *mem, uint16_t addr, uint8_t value);

#endif // GB_MEM_H
