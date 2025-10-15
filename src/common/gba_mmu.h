#ifndef GBA_MMU_H
#define GBA_MMU_H

#include <stdint.h>
#include <stddef.h>

#define GBA_ROM_SIZE 0x02000000 // 32 MB max ROM
#define GBA_RAM_SIZE 0x00040000 // 256 KB internal RAM

typedef struct {
    uint8_t rom[GBA_ROM_SIZE];
    uint8_t ram[GBA_RAM_SIZE];
} gba_mmu_t;

void gba_mmu_init(gba_mmu_t *mmu);
void gba_mmu_reset(gba_mmu_t *mmu);
int gba_mmu_load_rom(gba_mmu_t *mmu, const void *data, size_t size);

#endif // GBA_MMU_H
