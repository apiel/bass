#ifndef IO_STATE_H_
#define IO_STATE_H_

#include <Arduino.h>

#include "io_midi_core.h"
#include "io_util.h"

bool mcMode = false;
bool sdAvailable = true;

void toggleMcMode() { mcMode = !mcMode; }

void updateMcModeState() {
    for (byte n = 0; n < MIDI_COUNT; n++) {
        if (mcMode) {
            midi[n].sendNoteOn(16, 100, 11);
            midi[n].sendNoteOn(40, 100, 11);
        } else {
            midi[n].sendNoteOff(16, 100, 11);
            midi[n].sendNoteOff(40, 100, 11);
        }
    }
}

#endif
