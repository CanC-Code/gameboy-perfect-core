#ifndef GB_CPU_H
#define GB_CPU_H

#include <stdint.h>
#include <stdbool.h>
#include "mmu.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FLAG_Z 0x80
#define FLAG_N 0x40
#define FLAG_H 0x20
#define FLAG_C 0x10

typedef struct gb_cpu_s {
    uint8_t a, f;   // Accumulator & flags register
    uint8_t b, c;
    uint8_t d, e;
    uint8_t h, l;
    uint16_t sp;    // Stack pointer
    uint16_t pc;    // Program counter
    bool ime;       // Interrupt Master Enable
    bool halted;
    bool stopped;
} gb_cpu_t;

void gb_cpu_init(gb_cpu_t* cpu);
void gb_cpu_reset(gb_cpu_t* cpu);
void gb_cpu_step(gb_cpu_t* cpu, gb_mmu_t* mmu, int cycles);

// Flag helper macros
#define SET_FLAG(cpu, f)    ((cpu)->f |= (f))
#define CLEAR_FLAG(cpu, f)  ((cpu)->f &= ~(f))
#define IS_FLAG(cpu, f)     (((cpu)->f & (f)) != 0)
#define UPDATE_FLAG(cpu,f,cond) ((cond)?SET_FLAG(cpu,f):CLEAR_FLAG(cpu,f))

#ifdef __cplusplus
}
#endif

#endif /* GB_CPU_H */

