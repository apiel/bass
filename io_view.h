#ifndef IO_VIEW_H_
#define IO_VIEW_H_

#include <Arduino.h>

#include "instrument/io_audio_synth.h"
#include "io_instrument.h"
#include "io_util.h"
#include "io_view_state.h"

#define MAIN_VIEW_COUNT (SYNTH_COUNT)

void setCurrentView(int8_t direction) {
    currentView = mod(currentView + direction, MAIN_VIEW_COUNT);
}

void setSynthViewPos(byte pos) {
    Serial.println("setSynthViewPos");
    currentView = pos;
}

bool isSynthView() { return true; }

IO_AudioSynth* getSynth() { return &synth[currentView]; }

#endif
