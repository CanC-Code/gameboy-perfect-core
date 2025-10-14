#include "cpu.h"
#include <string.h>
#include <stdio.h>

/* Fetch 8-bit instruction */
static inline uint8_t cpu_fetch8(core_state_t *cs) {
    uint8_t val = mmu_read8(cs, cs->pc);
    cs->pc++;
    return val;
}

/* Fetch 16-bit instruction (little-endian) */
static inline uint16_t cpu_fetch16(core_state_t *cs) {
    uint16_t val = mmu_read16(cs, cs->pc);
    cs->pc += 2;
    return val;
}

/* CPU initialization */
void gb_cpu_init(core_state_t *cs) {
    cs->cpu = malloc(sizeof(gb_cpu_t));
    if (!cs->cpu) return;
    memset(cs->cpu, 0, sizeof(gb_cpu_t));
}

/* CPU reset (power-on) */
void gb_cpu_reset(core_state_t *cs) {
    gb_cpu_t *cpu = (gb_cpu_t *)cs->cpu;
    if (!cpu) return;

    cpu->af = 0x01B0;
    cpu->bc = 0x0013;
    cpu->de = 0x00D8;
    cpu->hl = 0x014D;
    cpu->sp = 0xFFFE;
    cpu->pc = 0x0100;
    cpu->ime = true;
    cpu->halted = false;
}

/* Execute one instruction */
static void cpu_execute_instruction(core_state_t *cs) {
    gb_cpu_t *cpu = (gb_cpu_t *)cs->cpu;
    uint8_t opcode = cpu_fetch8(cs);

    switch(opcode) {
        case 0x00: /* NOP */
            break;

        case 0x3E: { /* LD A, nn */
            uint8_t val = cpu_fetch8(cs);
            cpu->a = val;
            break;
        }

        case 0x06: { /* LD B, nn */
            uint8_t val = cpu_fetch8(cs);
            cpu->b = val;
            break;
        }

        case 0x0E: { /* LD C, nn */
            uint8_t val = cpu_fetch8(cs);
            cpu->c = val;
            break;
        }

        case 0xAF: /* XOR A */
            cpu->a ^= cpu->a;
            cpu->f = 0x80; /* Zero flag set */
            break;

        case 0xC3: { /* JP nn */
            uint16_t addr = cpu_fetch16(cs);
            cpu->pc = addr;
            break;
        }

        default:
            printf("Unimplemented opcode 0x%02X at 0x%04X\n", opcode, cpu->pc-1);
            break;
    }
}

/* Execute N cycles (simplified: 1 instruction = 4 cycles for now) */
void gb_cpu_step(core_state_t *cs, int cycles) {
    int executed = 0;
    while (executed < cycles) {
        cpu_execute_instruction(cs);
        executed += 4;
    }
}

/* Run until next VBlank (frame simulation placeholder) */
void gb_cpu_run_frame(core_state_t *cs) {
    gb_cpu_step(cs, 69905); /* Approximate cycles per 60Hz frame (DMG) */
}
