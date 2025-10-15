cmake_minimum_required(VERSION 3.10)
project(gameboy_perfect_core C)

# Use C11 standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Treat warnings as errors
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/src/common
)

# Source files
set(SOURCES
    src/common/core_state.c
    src/common/cpu.c
    src/common/ppu.c
    src/common/apu.c
)

# Build static library
add_library(gameboy_perfect_core STATIC ${SOURCES})

# Optional: build executable for testing
# add_executable(test_core src/main.c)
# target_link_libraries(test_core gameboy_perfect_core)
