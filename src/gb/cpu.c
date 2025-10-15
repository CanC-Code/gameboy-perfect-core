#include "cpu.h"
#include <string.h>

void gb_cpu_init(gb_cpu_t *cpu, uint8_t *ram, size_t size) {
    cpu->ram = ram;
    cpu->ram_size = size;
    gb_cpu_reset(cpu);
}

void gb_cpu_reset(gb_cpu_t *cpu) {
    memset(cpu->ram, 0, cpu->ram_size);
    cpu->a = 0x01;
    cpu->f = 0xB0;
    cpu->b = 0x00;
    cpu->c = 0x13;
    cpu->d = 0x00;
    cpu->e = 0xD8;
    cpu->h = 0x01;
    cpu->l = 0x4D;
    cpu->sp = 0xFFFE;
    cpu->pc = 0x0100;
    cpu->cycles = 0;
    gb_apu_reset(&cpu->apu);
}

uint8_t gb_cpu_read8(gb_cpu_t *cpu, uint16_t addr) {
    if (addr < cpu->ram_size) return cpu->ram[addr];
    return 0xFF;
}

void gb_cpu_write8(gb_cpu_t *cpu, uint16_t addr, uint8_t val) {
    if (addr < cpu->ram_size) cpu->ram[addr] = val;
}

void gb_cpu_step(gb_cpu_t *cpu) {
    // For simplicity, we assume 1 NOP per step initially
    cpu->cycles += 4;
    gb_apu_step(&cpu->apu, 4);
    // TODO: decode/execute real opcodes
}
