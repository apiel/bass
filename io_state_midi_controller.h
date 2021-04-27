#ifndef IO_STATE_MIDI_CONTROLLER_H_
#define IO_STATE_MIDI_CONTROLLER_H_

#include <Arduino.h>

#include "io_midi_core.h"
#include "io_view_state.h"

void updateCurrentViewStateOnMidiController() {
    if (!mcMode) {
        for (byte pos = 0; pos < 8; pos++) {
            if (currentView == pos) {
                noteOn(8 + pos);
                noteOn(32 + pos);
            } else {
                noteOff(8 + pos);
                noteOff(32 + pos);
            }
        }
    }
}

void updateMcModeStateOnMidiController() {
    if (mcMode) {
        noteOn(16);
        noteOn(40);
    } else {
        noteOff(16);
        noteOff(40);
    }
}

bool initStateOnMidiControllerDone = false;
void initStateOnMidiController() {
    if (!initStateOnMidiControllerDone) {
        initStateOnMidiControllerDone = true;
        updateCurrentViewStateOnMidiController();
        updateMcModeStateOnMidiController();
    }
}

#endif
