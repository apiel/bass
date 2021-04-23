#ifndef IO_VIEW_H_
#define IO_VIEW_H_

#include <Arduino.h>

#include "instrument/synth/io_audio_synth.h"
#include "io_instrument.h"
#include "io_util.h"

#define MAIN_VIEW_COUNT (SYNTH_COUNT + KICK_COUNT)

byte currentView = 0;

void setCurrentView(int8_t direction) {
    currentView = mod(currentView + direction, MAIN_VIEW_COUNT);
}

void setKickViewPos(byte pos) {
    currentView = pos;
}

void setSynthViewPos(byte pos) {
    Serial.println("setSynthViewPos");
    currentView = pos + KICK_COUNT;
}

bool isKickView() { return currentView < KICK_COUNT; }
bool isSynthView() { return !isKickView(); }

IO_AudioSynth* getSynth() { return &synth[currentView - KICK_COUNT]; }
IO_AudioKick* getKick() { return &kick[currentView]; }

#endif
