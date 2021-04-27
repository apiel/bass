#ifndef IO_AUDIO_SEQ_H_
#define IO_AUDIO_SEQ_H_

#include <Arduino.h>

#include "../Pattern.h"
#include "../io_pattern_storage.h"
#include "./io_audio_synth_core.h"

class IO_AudioSeq {
   private:
    IO_AudioSynthCore* core;
    // should it be a pointer or a copy?
    byte currentStep = 0;
    Step lastStep;

   public:
    bool active = false;
    byte currentPattern = 0;
    byte currentStepSelection = 0;
    Pattern* pattern;

    IO_AudioSeq(IO_AudioSynthCore* _core) { core = _core; }

    void init() { setCurrentPattern(0); }

    void setCurrentPattern(int8_t direction) {
        currentPattern += direction;
        pattern = &patterns[currentPattern];
    }

    void next() {
        Step* step = &pattern->steps[currentStep];
        bool triggerNoteOn = active && step->duration;
        if (!lastStep.tie || !triggerNoteOn) {
            core->noteOff(lastStep.note);
        }
        if (triggerNoteOn) {
            core->noteOn(step->note, step->velocity);
        }
        lastStep.set(step);
        currentStep = (currentStep + 1) % pattern->stepCount;
    }

    void toggle() { active = !active; }
    void activate(bool value = true) { active = value; }
};

#endif
