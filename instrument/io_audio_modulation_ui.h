#ifndef IO_AUDIO_MODULATION_UI_H_
#define IO_AUDIO_MODULATION_UI_H_

#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <Audio.h>

#include "../audio/AudioModulation.h"
#include "../io_display_util.h"
#include "../io_midi_util.h"
#include "./io_display_helper.h"

class IO_AudioModulationUI {
   private:
    AudioModulation *mod;

   public:
    IO_AudioModulationUI(AudioModulation *_mod) { mod = _mod; }

    void display(Adafruit_SSD1306 *d) {
        if (mod->modulationOn) {
            addToCursor(d, 0, 4);
            d->println("Modulation level");
            d->printf("%.2f|%.2f|%.2f|%.2f\n", mod->modLevel[0],
                      mod->modLevel[1], mod->modLevel[2], mod->modLevel[3]);
            d->printf("%.2f|%.2f|%.2f|%.2f\n", mod->modLevel[4],
                      mod->modLevel[5], mod->modLevel[6], mod->modLevel[7]);

            addToCursor(d, 0, 4);
            d->println("Modulation ms");
            d->printf("%d|%d|%d|%d\n", (int)mod->modMs[0], (int)mod->modMs[1],
                      (int)mod->modMs[2], (int)mod->modMs[3]);
            d->printf("%d|%d|%d|%d\n", (int)mod->modMs[4], (int)mod->modMs[5],
                      (int)mod->modMs[6], (int)mod->modMs[7]);
        } else {
            d->println("\nNo modulation");
        }
    }

    void noteOnHandler(byte channel, byte note, byte velocity) {}

    void noteOffHandler(byte channel, byte note, byte velocity) {}

    void controlChangeHandler(byte channel, byte knob, int8_t direction) {
        if (channel == 11) {
            if (knob == 1) {
                mod->setModLevel(0, direction);
            } else if (knob == 2) {
                mod->setModLevel(1, direction);
            } else if (knob == 3) {
                mod->setModLevel(2, direction);
            } else if (knob == 4) {
                mod->setModLevel(3, direction);
            } else if (knob == 5) {
                mod->setModLevel(4, direction);
            } else if (knob == 6) {
                mod->setModLevel(5, direction);
            } else if (knob == 7) {
                mod->setModLevel(6, direction);
            } else if (knob == 8) {
                mod->setModLevel(7, direction);
            } else if (knob == 11) {
                mod->setModMs(0, direction);
            } else if (knob == 12) {
                mod->setModMs(1, direction);
            } else if (knob == 13) {
                mod->setModMs(2, direction);
            } else if (knob == 14) {
                mod->setModMs(3, direction);
            } else if (knob == 15) {
                mod->setModMs(4, direction);
            } else if (knob == 16) {
                mod->setModMs(5, direction);
            } else if (knob == 17) {
                mod->setModMs(6, direction);
            } else if (knob == 0) {  // 0 for 18
                mod->setModMs(7, direction);
            }
        }
    }
};

#endif
