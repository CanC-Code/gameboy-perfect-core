#include "cpu.h"

// Initialize CPU and connect to MMU
void gba_cpu_init(gba_cpu_t *cpu, gba_mmu_t *mmu) {
    if (!cpu || !mmu) return;
    for (int i = 0; i < 16; i++) cpu->regs[i] = 0;
    cpu->cpsr = 0x00000000;
    cpu->mmu = mmu;
}

// Fetch 32-bit instruction from memory
uint32_t gba_cpu_fetch32(gba_cpu_t *cpu, uint32_t addr) {
    if (!cpu || !cpu->mmu) return 0xFFFFFFFF;
    uint32_t val = 0;
    val |= cpu->mmu->rom[addr - 0x08000000];
    val |= cpu->mmu->rom[addr - 0x08000000 + 1] << 8;
    val |= cpu->mmu->rom[addr - 0x08000000 + 2] << 16;
    val |= cpu->mmu->rom[addr - 0x08000000 + 3] << 24;
    return val;
}

// Minimal CPU step (placeholder)
void gba_cpu_step(gba_cpu_t *cpu) {
    // TODO: implement ARM7TDMI instruction decoding
    cpu->regs[15] += 4; // increment PC
}
