#ifndef LIBRETRO_H
#define LIBRETRO_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RETRO_API_VERSION 1

/* Devices */
#define RETRO_DEVICE_JOYPAD 1

/* Joypad IDs (common ones used) */
#define RETRO_DEVICE_ID_JOYPAD_B       0
#define RETRO_DEVICE_ID_JOYPAD_Y       1
#define RETRO_DEVICE_ID_JOYPAD_SELECT  2
#define RETRO_DEVICE_ID_JOYPAD_START   3
#define RETRO_DEVICE_ID_JOYPAD_UP      4
#define RETRO_DEVICE_ID_JOYPAD_DOWN    5
#define RETRO_DEVICE_ID_JOYPAD_LEFT    6
#define RETRO_DEVICE_ID_JOYPAD_RIGHT   7
#define RETRO_DEVICE_ID_JOYPAD_A       8
#define RETRO_DEVICE_ID_JOYPAD_X       9
#define RETRO_DEVICE_ID_JOYPAD_L       10
#define RETRO_DEVICE_ID_JOYPAD_R       11

/* Basic structs used by libretro cores */
struct retro_system_info {
    const char *library_name;
    const char *library_version;
    const char *valid_extensions;
    bool need_fullpath;
    bool block_extract;
};

struct retro_game_info {
    const char *path;      /* optional file path */
    const void *data;      /* pointer to loaded ROM data (may be NULL if need_fullpath) */
    size_t size;           /* size of data in bytes */
    const char *meta;      /* optional metadata */
};

struct retro_game_geometry {
    unsigned base_width;
    unsigned base_height;
    unsigned max_width;
    unsigned max_height;
    float aspect_ratio;
};

struct retro_system_timing {
    double fps;
    double sample_rate;
};

struct retro_system_av_info {
    struct retro_game_geometry geometry;
    struct retro_system_timing timing;
};

/* Callback types the frontend provides to the core */
typedef void (*retro_video_refresh_t)(const void *data, unsigned width, unsigned height, size_t pitch);
typedef void (*retro_audio_sample_t)(int16_t left, int16_t right);
typedef size_t (*retro_audio_sample_batch_t)(const int16_t *data, size_t frames);
typedef int16_t (*retro_input_state_t)(unsigned port, unsigned device, unsigned index, unsigned id);
typedef void (*retro_input_poll_t)(void);
typedef bool (*retro_environment_t)(unsigned cmd, void *data);

/* Device constants for retro_get_memory_* (stubs) */
enum {
    RETRO_MEMORY_SYSTEM_RAM = 0,
    RETRO_MEMORY_SAVE_RAM
};

/* Exported core functions the frontend will call.
 * The core must implement these (we declare them here for clarity).
 *
 * Note: This file is a minimal stub for compilation. For production,
 * use the official libretro headers from libretro.
 */

#ifdef __cplusplus
}
#endif

#endif /* LIBRETRO_H */
