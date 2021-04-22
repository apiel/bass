#ifndef IO_VIEW_H_
#define IO_VIEW_H_

#include <Arduino.h>

#include "instrument/synth/io_audio_synth.h"
#include "io_instrument.h"
#include "io_util.h"

// enum { VIEW_SYNTH, VIEW_COUNT };
// #define MAIN_VIEW_COUNT SYNTH_COUNT
#define MAIN_VIEW_COUNT 4

// byte currentView = SYNTH_0;
byte currentView = 0;

void setCurrentView(int8_t direction) {
    currentView = mod(currentView + direction, MAIN_VIEW_COUNT);
}

void setCurrentViewPos(byte pos) {
    currentView = pos;
}

bool isSynthView() { return true; }

IO_AudioSynth* getSynth() { return &synth[currentView]; }

#endif
