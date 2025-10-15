#!/bin/bash
set -e

echo "[*] Cleaning old build..."
rm -rf build
mkdir -p build
cd build

echo "[*] Configuring with CMake..."
cmake ..

echo "[*] Building..."
make -j$(nproc)

echo "[*] Done!"
echo "Output core: $(realpath gameboy_perfect_core_libretro.so)"
