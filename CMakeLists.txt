cmake_minimum_required(VERSION 3.15)
project(gameboy_perfect_core C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Set output library name
set(LIB_NAME "gameboy_perfect_core")

# Include directories
include_directories(
    include
    src
    src/common
    src/gb
    src/gba
)

# Core common sources
set(COMMON_SOURCES
    src/common/core_state.c
    src/common/timing.c
    src/common/libretro.c
    src/common/audio.c
)

# GB sources
set(GB_SOURCES
    src/gb/cpu.c
    src/gb/mmu.c
    src/gb/ppu.c
    src/gb/gb_apu.c
)

# GBA sources
set(GBA_SOURCES
    src/gba/cpu_stub.c
    src/gba/mmu.c
    src/gba/ppu.c
    src/gba/gba_apu.c
)

# Combine all sources
set(ALL_SOURCES
    ${COMMON_SOURCES}
    ${GB_SOURCES}
    ${GBA_SOURCES}
)

# Shared library (libretro core)
add_library(${LIB_NAME} SHARED ${ALL_SOURCES})

# Compiler flags
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${LIB_NAME} PRIVATE -Wall -Wextra -O2)
endif()

# Define macro for libretro build
target_compile_definitions(${LIB_NAME} PRIVATE -DLIBRETRO)

# Set output name for RetroArch
set_target_properties(${LIB_NAME} PROPERTIES PREFIX "lib" SUFFIX ".so")
