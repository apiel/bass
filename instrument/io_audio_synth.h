#ifndef IO_AUDIO_SYNTH_H_
#define IO_AUDIO_SYNTH_H_

#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <Audio.h>

#include "./io_audio_effect_ui.h"
#include "./io_audio_filter_ui.h"
#include "./io_audio_modulation_ui.h"
#include "./io_audio_seq.h"
#include "./io_audio_seq_ui.h"
#include "./io_audio_synth_core.h"
#include "./io_audio_synth_ui.h"

class IO_AudioSynth : public IO_AudioSynthCore {
   protected:
    enum {
        VIEW_CORE,
        VIEW_FILTER,
        VIEW_EFFECT,
        VIEW_MODULATION,
        VIEW_SEQ,
        VIEW_COUNT
    };
    byte currentView = VIEW_CORE;

   public:
    byte id = 0;
    IO_AudioSynthCoreUI* coreUI;
    IO_AudioSeq* seq;
    IO_AudioSeqUI* seqUI;
    IO_AudioFilterUI* filterUI;
    IO_AudioEffectUI* effectUI;
    IO_AudioModulationUI* modUI;

    IO_AudioSynth() {
        coreUI = new IO_AudioSynthCoreUI(this);
        seq = new IO_AudioSeq(this);
        seqUI = new IO_AudioSeqUI(seq);
        filterUI = new IO_AudioFilterUI(&filter);
        effectUI = new IO_AudioEffectUI(&effect);
        modUI = new IO_AudioModulationUI(&freqMod);
    }

    void init(byte _id) {
        seq->init();
        id = _id;
    }

    void display(Adafruit_SSD1306* d) {
        d->clearDisplay();
        d->setCursor(0, 0);
        d->printf("%d %s\n", id, isDrum ? "Drum" : "Synth");

        switch (currentView) {
            case VIEW_SEQ:
                seqUI->display(d);
                break;

            case VIEW_FILTER:
                filterUI->display(d);
                break;

            case VIEW_EFFECT:
                effectUI->display(d);
                break;

            case VIEW_MODULATION:
                modUI->display(d);
                break;

            default:
                coreUI->display(d);
                break;
        }
        // display playing status on all the views
        seqUI->displayPlayingStatus(d);
    }

    void setCurrentView(int8_t direction) {
        currentView = mod(currentView + direction, VIEW_COUNT);
        // Serial.printf("Current view %d\n", currentView);
    }

    void noteOnHandler(byte channel, byte note, byte velocity) {
        if (note == 18 || note == 42) {
            setCurrentView(-1);
        } else if (note == 19 || note == 43) {
            setCurrentView(1);
        } else if (note == 21 || note == 45) {
            noteOn();
        } else if (note == 22 || note == 46) {
            seq->toggle();
        } else {
            switch (currentView) {
                case VIEW_SEQ:
                    seqUI->noteOnHandler(channel, note, velocity);
                    break;

                case VIEW_FILTER:
                    filterUI->noteOnHandler(channel, note, velocity);
                    break;

                case VIEW_EFFECT:
                    effectUI->noteOnHandler(channel, note, velocity);
                    break;

                case VIEW_MODULATION:
                    modUI->noteOnHandler(channel, note, velocity);
                    break;

                case VIEW_CORE:
                    coreUI->noteOnHandler(channel, note, velocity);
                    break;
            }
        }
    }

    void noteOffHandler(byte channel, byte note, byte velocity) {
        if (note == 21 || note == 45) {
            noteOff();
        } else {
            switch (currentView) {
                case VIEW_SEQ:
                    seqUI->noteOffHandler(channel, note, velocity);
                    break;

                case VIEW_FILTER:
                    filterUI->noteOffHandler(channel, note, velocity);
                    break;

                case VIEW_EFFECT:
                    effectUI->noteOffHandler(channel, note, velocity);
                    break;

                case VIEW_MODULATION:
                    modUI->noteOffHandler(channel, note, velocity);
                    break;

                case VIEW_CORE:
                    coreUI->noteOffHandler(channel, note, velocity);
                    break;
            }
        }
    }

    void controlChangeHandler(byte channel, byte knob, int8_t direction) {
        switch (currentView) {
            case VIEW_SEQ:
                seqUI->controlChangeHandler(channel, knob, direction);
                break;

            case VIEW_FILTER:
                filterUI->controlChangeHandler(channel, knob, direction);
                break;

            case VIEW_EFFECT:
                effectUI->controlChangeHandler(channel, knob, direction);
                break;

            case VIEW_MODULATION:
                modUI->controlChangeHandler(channel, knob, direction);
                break;

            case VIEW_CORE:
                coreUI->controlChangeHandler(channel, knob, direction);
                break;
        }
    }
};

#endif
