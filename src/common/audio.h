#ifndef AUDIO_H
#define AUDIO_H

#include <stdint.h>

void audio_init(void);
void audio_sample(int16_t left, int16_t right);
void audio_update(void);

#endif // AUDIO_H
