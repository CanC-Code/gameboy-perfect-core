#include "gba_cpu.h"

// Initialize CPU
void gba_cpu_init(gba_cpu_t *cpu, gba_mmu_t *mmu) {
    cpu->mmu = mmu;
    gba_cpu_reset(cpu);
}

// Reset CPU
void gba_cpu_reset(gba_cpu_t *cpu) {
    for (int i = 0; i < 16; i++)
        cpu->regs[i] = 0;
    cpu->regs[15] = 0x08000000; // PC starts at ROM base
    cpu->cpsr = 0x0000001F;     // Supervisor mode
}

// Step CPU (placeholder: advance PC)
void gba_cpu_step(gba_cpu_t *cpu) {
    // Fetch instruction (placeholder, 32-bit ARM instruction)
    uint32_t pc = cpu->regs[15];
    uint32_t instr = cpu->mmu->rom[pc - 0x08000000];

    // Decode & execute (placeholder)
    cpu->regs[15] += 4; // Advance PC by 4 bytes
}
