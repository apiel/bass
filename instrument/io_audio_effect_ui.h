#ifndef IO_AUDIO_EFFECT_UI_H_
#define IO_AUDIO_EFFECT_UI_H_

#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <Audio.h>

#include "../io_display_util.h"
#include "../io_midi_util.h"
#include "./io_audio_synth_core.h"
#include "./io_display_helper.h"

class IO_AudioEffectUI {
   private:
    IO_AudioSynthCore* core;

   public:
    IO_AudioEffectUI(IO_AudioSynthCore* _core) { core = _core; }

    void display(Adafruit_SSD1306* d) {
        addToCursor(d, 0, 4);
        d->println("Effect");

        addToCursor(d, 0, 4);
        d->printf("Dist %d range %d\n", (int)core->distortion.amount,
                  (int)core->distortion.range);
    }

    void noteOnHandler(byte channel, byte note, byte velocity) {}

    void noteOffHandler(byte channel, byte note, byte velocity) {}

    void controlChangeHandler(byte channel, byte knob, int8_t direction) {
        if (channel == 11) {
            if (knob == 1) {
                core->setDistortion(direction);
            } else if (knob == 2) {
                core->setDistortionRange(direction);
            } else if (knob == 3) {
            } else if (knob == 4) {
            } else if (knob == 5) {
            } else if (knob == 6) {
            } else if (knob == 7) {
            } else if (knob == 8) {
            } else if (knob == 11) {
            } else if (knob == 12) {
            } else if (knob == 13) {
            } else if (knob == 14) {
            } else if (knob == 15) {
            } else if (knob == 16) {
            } else if (knob == 17) {
            } else if (knob == 0) {  // 0 for 18
            }
        }
    }
};

#endif
