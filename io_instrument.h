#ifndef IO_INSTRUMENT_H_
#define IO_INSTRUMENT_H_

#include <Arduino.h>

#include "instrument/synth/io_audio_synth.h"

// #define SYNTH_COUNT 4

enum { SYNTH_0, SYNTH_1, SYNTH_2, SYNTH_3, SYNTH_COUNT };

IO_AudioSynth synth[SYNTH_COUNT];

#endif
