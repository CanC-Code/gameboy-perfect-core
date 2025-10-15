#ifndef GB_APU_H
#define GB_APU_H

typedef struct gb_apu_s {
    // Example APU state
    unsigned char nr10, nr11, nr12, nr13, nr14;
} gb_apu_t;

void gb_apu_reset( gb_apu_t *apu );

#endif // GB_APU_H
