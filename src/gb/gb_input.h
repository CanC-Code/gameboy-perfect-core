#ifndef GB_INPUT_H
#define GB_INPUT_H

#include <stdint.h>
#include <stdbool.h>

typedef struct gb_input_s {
    bool buttons[8]; // A, B, Select, Start, Right, Left, Up, Down
} gb_input_t;

enum {
    GB_BUTTON_A = 0,
    GB_BUTTON_B,
    GB_BUTTON_SELECT,
    GB_BUTTON_START,
    GB_BUTTON_RIGHT,
    GB_BUTTON_LEFT,
    GB_BUTTON_UP,
    GB_BUTTON_DOWN
};

void gb_input_init(gb_input_t *input);
void gb_input_reset(gb_input_t *input);
void gb_input_press(gb_input_t *input, int button);
void gb_input_release(gb_input_t *input, int button);
bool gb_input_is_pressed(gb_input_t *input, int button);

#endif // GB_INPUT_H
