#ifndef GB_CART_H
#define GB_CART_H

#include <stdint.h>
#include <stdbool.h>

typedef struct gb_cart_s {
    uint8_t rom[0x8000];  // simplified fixed ROM area
    uint8_t ram[0x2000];  // simplified cartridge RAM
    bool loaded;
} gb_cart_t;

void gb_cart_init(gb_cart_t *cart);
bool gb_cart_load(gb_cart_t *cart, const uint8_t *data, size_t size);
void gb_cart_unload(gb_cart_t *cart);

#endif // GB_CART_H
