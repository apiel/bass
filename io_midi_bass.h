#ifndef IO_MIDI_KICK_H_
#define IO_MIDI_KICK_H_

#include <Arduino.h>

#include "io_audio.h"
#include "io_midi_util.h"
#include "io_state.h"

void kickNoteOnHandler(byte channel, byte note, byte velocity) {
    if (channel == 11) {
        byte key = getItemKey(note);
        if (key != 255) {
            // currentkick = key;
        } else if (note == 22 || note == 46) {
            bass.noteOn();
        } else if (note == 23 || note == 47) {
            // savekick(currentkick);
        } else if (note == 20) {
        } else if (note == 17 || note == 41) {
            if (mcMode) {
                bass.toggleModulation();
            } else {
                bass.toggleRectifier();
            }
        }
    }
}

void kickNoteOffHandler(byte channel, byte note, byte velocity) {
    if (channel == 11) {
        if (note == 22 || note == 46) {
            bass.noteOff();
        }
    }
}

void kickControlChangeHandler(byte channel, byte knob, int8_t direction) {
    if (channel == 11) {
        if (knob == 1) {
            if (mcMode) {
                bass.setModLevel(0, direction);
            } else {
                bass.waveform.setNextWaveform(direction);
            }
        } else if (knob == 2) {
            if (mcMode) {
                bass.setModLevel(1, direction);
            } else {
                bass.waveform.setFrequency(direction);
            }
        } else if (knob == 3) {
            if (mcMode) {
                bass.setModLevel(2, direction);
            } else {
                bass.waveform.setAmplitude(direction);
            }
        } else if (knob == 4) {
            if (mcMode) {
                bass.setModLevel(3, direction);
            } else {
            }
        } else if (knob == 5) {
            if (mcMode) {
                bass.setModLevel(4, direction);
            } else {
            }
        } else if (knob == 6) {
            if (mcMode) {
                bass.setModLevel(5, direction);
            } else {
                bass.waveform.setStart(direction);
            }
        } else if (knob == 7) {
            if (mcMode) {
                bass.setModLevel(6, direction);
            } else {
                bass.setAttack(direction);
            }
        } else if (knob == 8) {
            if (mcMode) {
                bass.setModLevel(7, direction);
            } else {
                bass.setDecay(direction);
            }
        } else if (knob == 11) {
            if (mcMode) {
                bass.setModMs(0, direction);
            } else {
                bass.setCurrentFilter(direction);
            }
        } else if (knob == 12) {
            if (mcMode) {
                bass.setModMs(1, direction);
            } else {
                bass.setFilterFrequency(direction);
            }
        } else if (knob == 13) {
            if (mcMode) {
                bass.setModMs(2, direction);
            } else {
                bass.setFilterResonance(direction);
            }
        } else if (knob == 14) {
            if (mcMode) {
                bass.setModMs(3, direction);
            } else {
            }
        } else if (knob == 15) {
            if (mcMode) {
                bass.setModMs(4, direction);
            } else {
            }
        } else if (knob == 16) {
            if (mcMode) {
                bass.setModMs(5, direction);
            } else {
                bass.setDistortion(direction);
            }
        } else if (knob == 17) {
            if (mcMode) {
                bass.setModMs(6, direction);
            } else {
                bass.setDistortionRange(direction);
            }
        } else if (knob == 0) {  // 0 for 18
            if (mcMode) {
                bass.setModMs(7, direction);
            } else {
                bass.setBitcrusher(direction);
            }
        }
    }
}

#endif
