#ifndef STEP_H_
#define STEP_H_

#include "./audio/note.h"

#define BASE_FREQ _C4

class Step {
   public:
    byte note = BASE_FREQ;
    byte duration = 0;
    byte velocity = 100;
    bool tie = false;
    int freqDiff = 0;

    Step() {}

    void clear() { duration = 0; }

    void set(Step* step) {
        set(step->note, step->duration, step->velocity, step->tie);
    }

    void set(byte _note) {
        note = _note;
        freqDiff = NOTE_FREQ[BASE_FREQ] - NOTE_FREQ[note];
    }

    void set(byte _note, byte _duration) {
        duration = _duration;
        set(_note);
    }

    void set(byte _note, byte _duration, byte _velocity) {
        velocity = _velocity;
        set(_note, _duration);
    }

    void set(byte _note, byte _duration, byte _velocity, bool _tie) {
        tie = _tie;
        set(_note, _duration, _velocity);
    }
};

#endif
