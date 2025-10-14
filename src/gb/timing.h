#ifndef CORE_COMMON_H
#define CORE_COMMON_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

// Modes
typedef enum {
    MODE_UNSET = 0,
    MODE_GB,
    MODE_GBC,
    MODE_GBA
} core_mode_t;

// Pixel type (8-bit grayscale for GB/GBC, 32-bit ARGB for GBA)
typedef uint32_t pixel_t;

// Screen dimensions
#define GB_WIDTH 160
#define GB_HEIGHT 144
#define GBA_WIDTH 240
#define GBA_HEIGHT 160

#endif // CORE_COMMON_H
