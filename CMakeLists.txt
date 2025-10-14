cmake_minimum_required(VERSION 3.6)
project(gameboy_perfect_core C)

set(CMAKE_C_STANDARD 11)
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

# Sources
file(GLOB COMMON_SOURCES "${SRC_DIR}/common/*.c")
file(GLOB GB_SOURCES "${SRC_DIR}/gb/*.c")
file(GLOB GBA_SOURCES "${SRC_DIR}/gba/*.c")

add_library(gameboy_perfect_core SHARED
    ${COMMON_SOURCES}
    ${GB_SOURCES}
    ${GBA_SOURCES}
)

# include paths (add include/ and source dirs)
target_include_directories(gameboy_perfect_core PRIVATE
    ${INCLUDE_DIR}
    ${SRC_DIR}/common
    ${SRC_DIR}/gb
    ${SRC_DIR}/gba
)

set_target_properties(gameboy_perfect_core PROPERTIES POSITION_INDEPENDENT_CODE ON)
