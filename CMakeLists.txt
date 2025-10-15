cmake_minimum_required(VERSION 3.10)
project(gameboy_perfect_core C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(SRC
    src/common/audio.c
    src/common/apu.c
    src/common/core_state.c
    src/common/cpu.c
    src/common/gba_cpu.c
    src/common/gba_mmu.c
    src/common/libretro.c
    src/common/ppu.c
)

include_directories(
    include
    include/libretro-common/include
)

add_library(gameboy_perfect_core_libretro SHARED ${SRC})

set_target_properties(gameboy_perfect_core_libretro PROPERTIES
    PREFIX ""
    OUTPUT_NAME "gameboy_perfect_core_libretro"
)
