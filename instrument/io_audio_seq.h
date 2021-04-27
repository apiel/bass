#ifndef IO_AUDIO_SEQ_H_
#define IO_AUDIO_SEQ_H_

#include <Arduino.h>

#include "../Pattern.h"
#include "../io_config.h"
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
    byte currentRow = 0;
    Pattern* pattern;

    IO_AudioSeq(IO_AudioSynthCore* _core) { core = _core; }

    void init() { setCurrentPattern(0); }

    void setCurrentPattern(int8_t direction) {
        currentPattern += direction;
        pattern = &patterns[currentPattern];
    }

    void setCurrentStepSelection(int8_t direction) {
        currentStepSelection =
            mod(currentStepSelection + direction, STEP_COUNT);
    }

    void setCurrentRow(int8_t direction) {
        currentRow = mod(currentRow + direction, STEP_COUNT / 8);
    }

    void setStepNote(int8_t direction) {
        Step* pStep = &pattern->steps[currentStepSelection];
        pStep->set(constrain(pStep->note + direction, _C0, _B8));
    }

    void setStepVelocity(int8_t direction) {
        Step* pStep = &pattern->steps[currentStepSelection];
        pStep->velocity = constrain(pStep->velocity + direction, 0, 127);
    }

    void setStepDurationAndTie() {
        Step* pStep = &pattern->steps[currentStepSelection];
        if (!pStep->duration) {
            pStep->duration = 1;
            pStep->tie = false;
        } else if (pStep->tie) {
            pStep->duration = 0;
            pStep->tie = false;
        } else {
            pStep->tie = true;
        }
    }

    void toggleStep(byte pos) {
        currentStepSelection = pos + currentRow * 8;
        Step* pStep = &pattern->steps[currentStepSelection];
        if (!pStep->duration) {
            pStep->duration = 1;
            // pStep->tie = false;
        } else {
            pStep->duration = 0;
            // pStep->tie = false;
        }
    }

    void toggleTie() {
        Step* pStep = &pattern->steps[currentStepSelection];
        pStep->tie = !pStep->tie;
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
