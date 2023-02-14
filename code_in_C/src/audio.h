#ifndef AUDIO_H
#define AUDIO_H
#include <stdio.h>
#include <stdlib.h>
#include "../include/SDL.h"
struct AudioShenanigans{
  SDL_AudioSpec wavSpec;
  Uint8* wavStart;
  Uint32 wavLength;
  SDL_AudioDeviceID dvce;
  int success;
};
typedef struct AudioShenanigans AudioShenanigans;


typedef uint32_t uint32;
AudioShenanigans AUDIOLOAAAAAD(char *pathofwav, AudioShenanigans a);

#endif