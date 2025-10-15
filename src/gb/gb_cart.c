#include "gb_cart.h"
#include <string.h>

void gb_cart_init(gb_cart_t *cart) {
    if (!cart) return;
    memset(cart, 0, sizeof(gb_cart_t));
}

bool gb_cart_load(gb_cart_t *cart, const uint8_t *data, size_t size) {
    if (!cart || !data || size == 0) return false;
    size_t copy_size = size < sizeof(cart->rom) ? size : sizeof(cart->rom);
    memcpy(cart->rom, data, copy_size);
    cart->loaded = true;
    return true;
}

void gb_cart_unload(gb_cart_t *cart) {
    if (!cart) return;
    memset(cart, 0, sizeof(gb_cart_t));
}
