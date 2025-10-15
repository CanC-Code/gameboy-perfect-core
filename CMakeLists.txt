cmake_minimum_required(VERSION 3.15)
project(gameboy_perfect_core C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# --- Source files ---
set(GB_SOURCES
    src/gb/cpu.c
    src/gb/mmu.c
    src/gb/ppu.c
    src/gb/gb_apu.c
    src/gb/gb_ppu.c
    src/gb/cpu_stub.c
)

set(COMMON_SOURCES
    src/common/core_state.c
    src/common/timing.c
    src/common/audio.c
    src/common/libretro.c
    src/common/gba_cpu.c
    src/common/gba_mmu.c
)

set(GBA_SOURCES
    src/gba/gba_cpu.c
    src/gba/gba_mmu.c
    src/gba/ppu.c
    src/gba/gba_ppu.c
    src/gba/gba_apu.c
    src/gba/gba_core.c
    src/gba/core_state.c
    src/gba/cpu.c
    src/gba/cpu_stub.c
    src/gba/mmu.c
)

# Combine sources
set(ALL_SOURCES
    ${GB_SOURCES}
    ${COMMON_SOURCES}
    ${GBA_SOURCES}
)

# --- Include directories ---
include_directories(
    src/gb
    src/common
    src/gba
    include
)

# --- Output executable or library ---
add_library(gameboy_perfect_core STATIC ${ALL_SOURCES})

# Optional: set warnings and optimization flags
target_compile_options(gameboy_perfect_core PRIVATE
    -Wall -Wextra -Wpedantic -O2
)

# If you want a standalone executable instead:
# add_executable(gameboy_perfect_core ${ALL_SOURCES})
