#include "cpu.h"
#include "gba_mmu.h"
#include "gba_ppu.h"

typedef struct gba_core_t {
    gba_mmu_t mmu;
    gba_cpu_t cpu;
    gba_ppu_t ppu;
} gba_core_t;

void gba_core_init(gba_core_t *core, uint8_t *rom, uint32_t rom_size) {
    gba_mmu_init(&core->mmu, rom, rom_size);
    gba_cpu_init(&core->cpu, &core->mmu);
    gba_ppu_init(&core->ppu, &core->mmu);
}

void gba_core_step(gba_core_t *core) {
    gba_cpu_step(&core->cpu);
    gba_ppu_step(&core->ppu);
}
