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

    void display(Adafruit_SSD1306* d) { coreUI->display(d); }

    void noteOnHandler(byte channel, byte note, byte velocity) {
        coreUI->noteOnHandler(channel, note, velocity);
    }

    void noteOffHandler(byte channel, byte note, byte velocity) {
        coreUI->noteOffHandler(channel, note, velocity);
    }

    void controlChangeHandler(byte channel, byte knob, int8_t direction) {
        coreUI->controlChangeHandler(channel, knob, direction);
    }
};

#endif
