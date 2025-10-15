#ifndef APU_H
#define APU_H

#include <stdint.h>
#include <stddef.h>

typedef struct gb_apu_s {
    // Add audio state here
} gb_apu_t;

void gb_apu_reset(gb_apu_t *apu);
void gb_apu_step(gb_apu_t *apu);

#endif /* APU_H */
