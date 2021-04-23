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
        // } else if (note == 18 || note == 42) {
        //     setCurrentView(-1);
        //     return true;
        // } else if (note == 19 || note == 43) {
        //     setCurrentView(1);
        //     return true;
    } else if (note == 8) {
        // todo to be fixed
        setCurrentViewPos(KICK_0);
        return true;
    } else if (note == 9) {
        setCurrentViewPos(KICK_0);
        return true;
    } else if (note == 10) {
        setCurrentViewPos(SYNTH_0);
        return true;
    } else if (note == 11) {
        setCurrentViewPos(SYNTH_1);
        return true;
    } else if (note == 12) {
        setCurrentViewPos(SYNTH_2);
        return true;
    } else if (note == 13) {
        setCurrentViewPos(SYNTH_3);
        return true;
    }
    return false;
}

#endif
