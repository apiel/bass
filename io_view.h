#ifndef IO_VIEW_H_
#define IO_VIEW_H_

#include <Arduino.h>

#include "instrument/synth/io_audio_synth.h"
#include "io_instrument.h"
#include "io_util.h"

// enum { VIEW_SYNTH, VIEW_COUNT };
// #define MAIN_VIEW_COUNT SYNTH_COUNT + KICK_VIEW
#define MAIN_VIEW_COUNT 6

// byte currentView = SYNTH_0;
byte currentView = 0;

void setCurrentView(int8_t direction) {
    currentView = mod(currentView + direction, MAIN_VIEW_COUNT);
}

void setCurrentViewPos(byte pos) {
    currentView = pos;
}

// ToDo to be fixed
bool isSynthView() { return false; }
bool isKickView() { return true; }

IO_AudioSynth* getSynth() { return &synth[currentView]; }
IO_AudioKick* getKick() { return &kick[currentView]; }

#endif
