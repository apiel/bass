#ifndef IO_MIDI_DEFAULT_H_
#define IO_MIDI_DEFAULT_H_

#include <Arduino.h>

#include "io_instrument.h"
#include "io_state.h"
#include "io_view.h"

bool defaultNoteOnHandler(byte channel, byte note, byte velocity) {
    if (note == 16 || note == 40) {
        toggleGcMode();
        return true;
    } else if (note == 8 || note == 32) {
        setSynthViewPos(SYNTH_0);
        return true;
    } else if (note == 9 || note == 33) {
        setSynthViewPos(SYNTH_1);
        return true;
    } else if (note == 10 || note == 34) {
        setSynthViewPos(SYNTH_2);
        return true;
    } else if (note == 11 || note == 35) {
        setSynthViewPos(SYNTH_3);
        return true;
    }
    return false;
}

#endif
