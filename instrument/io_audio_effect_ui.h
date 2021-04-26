#ifndef IO_AUDIO_EFFECT_UI_H_
#define IO_AUDIO_EFFECT_UI_H_

#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <Audio.h>

#include "../effect/AudioEffect.h"
#include "../io_display_util.h"
#include "../io_midi_util.h"
#include "./io_display_helper.h"

class IO_AudioEffectUI {
   private:
    AudioEffect* effect;

   public:
    IO_AudioEffectUI(AudioEffect* _effect) { effect = _effect; }

    void display(Adafruit_SSD1306* d) {
        addToCursor(d, 0, 4);
        d->println("Effect");

        addToCursor(d, 0, 4);
        d->printf("Dist %d range %d\n", (int)effect->distortion.amount,
                  (int)effect->distortion.range);

        d->printf("Bitcrusher %d\n", (int)effect->xcrushBits);
        d->printf("Rectifier %s\n", effect->rectifierOn ? "ON" : "OFF");
    }

    void noteOnHandler(byte channel, byte note, byte velocity) {
        if (note == 17 || note == 41) {
            effect->toggleRectifier();
        }
    }

    void noteOffHandler(byte channel, byte note, byte velocity) {}

    void controlChangeHandler(byte channel, byte knob, int8_t direction) {
        if (channel == 11) {
            if (knob == 1) {
                effect->setDistortion(direction);
            } else if (knob == 2) {
                effect->setDistortionRange(direction);
            } else if (knob == 3) {
                effect->setBitcrusher(direction);
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
