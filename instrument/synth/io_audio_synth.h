#ifndef IO_AUDIO_SYNTH_H_
#define IO_AUDIO_SYNTH_H_

#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <Audio.h>

#include "./io_audio_synth_core.h"
#include "./io_audio_synth_seq.h"
#include "./io_audio_synth_seq_ui.h"
#include "./io_audio_synth_ui.h"

class IO_AudioSynth : public IO_AudioSynthCore {
   protected:
    enum { VIEW_CORE, VIEW_SEQ, VIEW_COUNT };
    byte currentView = VIEW_CORE;

   public:
    IO_AudioSynthCoreUI* coreUI;
    IO_AudioSynthSeq* seq;
    IO_AudioSynthSeqUI* seqUI;

    IO_AudioSynth() {
        coreUI = new IO_AudioSynthCoreUI(this);
        seq = new IO_AudioSynthSeq(this);
        seqUI = new IO_AudioSynthSeqUI(this, seq);
    }

    void init() { seq->init(); }

    void display(Adafruit_SSD1306* d) {
        switch (currentView) {
            case VIEW_SEQ:
                seqUI->display(d);
                break;

            default:
                coreUI->display(d);
                break;
        }
    }

    void setCurrentView(int8_t direction) {
        currentView = mod(currentView + direction, VIEW_COUNT);
    }

    void noteOnHandler(byte channel, byte note, byte velocity) {
        if (note == 18 || note == 42) {
            setCurrentView(-1);
        } else if (note == 19 || note == 43) {
            setCurrentView(1);
        } else {
            coreUI->noteOnHandler(channel, note, velocity);
        }
    }

    void noteOffHandler(byte channel, byte note, byte velocity) {
        coreUI->noteOffHandler(channel, note, velocity);
    }

    void controlChangeHandler(byte channel, byte knob, int8_t direction) {
        coreUI->controlChangeHandler(channel, knob, direction);
    }
};

#endif