#ifndef IO_INSTRUMENT_H_
#define IO_INSTRUMENT_H_

#include <Arduino.h>

#include "instrument/synth/io_audio_synth.h"
#include "instrument/kick/io_audio_kick.h"

// #define SYNTH_COUNT 4

enum { SYNTH_0, SYNTH_1, SYNTH_2, SYNTH_3, SYNTH_COUNT };
enum { KICK_0, KICK_1, KICK_COUNT };

IO_AudioSynth synth[SYNTH_COUNT];
IO_AudioKick kick[KICK_COUNT];

#endif
