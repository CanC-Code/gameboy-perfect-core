#include "timing.h"
#include "core_state.h"

// Timing-specific function
uint64_t cycles_per_frame_for_mode(core_mode_t m) {
    switch (m) {
        case MODE_GBA: return 16777216ULL / 60ULL; // ~279620 cycles/frame
        default: return 4194304ULL / 60ULL;       // ~69905 cycles/frame
    }
}
