#include "gb_apu.h"

void gb_apu_init(gb_apu_t *apu)
{
    apu->buffer_pos = 0;
}

void gb_apu_step(gb_apu_t *apu, int cycles)
{
    // placeholder
}

void gb_apu_reset(gb_apu_t *apu)
{
    apu->buffer_pos = 0;
}
