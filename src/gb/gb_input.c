#include "gb_input.h"
#include <string.h>

void gb_input_init(gb_input_t *input) {
    if (!input) return;
    memset(input, 0, sizeof(gb_input_t));
}

void gb_input_reset(gb_input_t *input) {
    if (!input) return;
    memset(input, 0, sizeof(gb_input_t));
}

void gb_input_press(gb_input_t *input, int button) {
    if (!input || button < 0 || button >= 8) return;
    input->buttons[button] = true;
}

void gb_input_release(gb_input_t *input, int button) {
    if (!input || button < 0 || button >= 8) return;
    input->buttons[button] = false;
}

bool gb_input_is_pressed(gb_input_t *input, int button) {
    if (!input || button < 0 || button >= 8) return false;
    return input->buttons[button];
}
