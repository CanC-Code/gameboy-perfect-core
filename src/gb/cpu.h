#ifndef GB_CPU_H
#define GB_CPU_H

#include "../common/core_state.h"

void cpu_reset(core_state_t *state);
void cpu_step(core_state_t *state);

#endif // GB_CPU_H
