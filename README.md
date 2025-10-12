# GameBoy Perfect Core

Cycle-accurate Game Boy / Game Boy Color emulator core for Android aarch64.

## Goals
- Pixel-perfect, shader-driven display matching real Game Boy
- Cycle-accurate CPU, PPU, and APU
- Audio output optimized for Android AAudio / Dolby Atmos
- Optional BIOS-free boot via HLE

## Folder structure
- src/ : core source files
- include/ : headers
- platform/ : Android platform glue
- tests/ : test harness & Blargg/mooneye tests
- shaders/ : OpenGL ES shaders
- assets/ : palettes, LUTs, sample ROMs
- build/ : compilation artifacts
- docs/ : documentation
