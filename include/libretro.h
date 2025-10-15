#ifndef LIBRETRO_H
#define LIBRETRO_H

#include <stdint.h>
#include <stdbool.h>   // <<-- needed for 'bool'

struct retro_game_geometry {
    unsigned width;
    unsigned height;
    unsigned max_width;
    unsigned max_height;
    float aspect_ratio;
};

typedef bool (*retro_environment_t)(unsigned cmd, void *data);

#endif
