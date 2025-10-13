## Using in RetroArch
Copy `libgameboy_perfect_core.so` into RetroArch cores folder and load a ROM (extensions: `.gb`, `.gbc`, `.gba`). The core will detect mode heuristically.

## Next steps
- Replace `cpu_stub` with a full LR35902 CPU and ARM7TDMI for GBA to get full emulation.
- Integrate APU for audio.
