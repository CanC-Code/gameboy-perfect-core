#include "cpu_stub.h"
#include <string.h>

void gb_cpu_init(struct gb_cpu_t *cpu) {
    if (!cpu) return;
    memset(cpu, 0, sizeof(struct gb_cpu_t));
    cpu->pc = 0x0100; // Start at typical GB entry point
    cpu->sp = 0xFFFE;
    cpu->halted = false;
    cpu->cycles = 0;
}

void gb_cpu_step(struct gb_cpu_t *cpu) {
    if (!cpu || cpu->halted) return;

    // Stub: simply increment PC and cycles
    cpu->pc += 1;
    cpu->cycles += 4; // assume each stub instruction takes 4 cycles
}
