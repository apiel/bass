#ifndef IO_AUDIO_FILTER_UI_H_
#define IO_AUDIO_FILTER_UI_H_

#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <Audio.h>

#include "../io_display_util.h"
#include "../io_midi_util.h"
#include "./io_audio_synth_core.h"
#include "./io_display_helper.h"

class IO_AudioFilterUI {
   private:
    AudioFilter *filter;

   public:
    IO_AudioFilterUI(AudioFilter *_filter) { filter = _filter; }

    void display(Adafruit_SSD1306 *d) {
        addToCursor(d, 0, 4);
        d->printf("%s %.1fHz %d\n", getFilter(filter->currentFilter),
                  filter->filterFrequency, filter->filterResonance);
        d->printf("%.1f %d|%d|%d%%|%d\n", filter->dcValue, (int)filter->adsr[0],
                  (int)filter->adsr[1], (int)(filter->adsr[2] * 100.0),
                  (int)filter->adsr[3]);
    }

    void noteOnHandler(byte channel, byte note, byte velocity) {}

    void noteOffHandler(byte channel, byte note, byte velocity) {}

    void controlChangeHandler(byte channel, byte knob, int8_t direction) {
        if (channel == 11) {
            if (knob == 1) {
                filter->setCurrentFilter(direction);
            } else if (knob == 2) {
                filter->setFilterFrequency(direction);
            } else if (knob == 3) {
                filter->setFilterResonance(direction);
            } else if (knob == 4) {
                filter->setDc(direction);
            } else if (knob == 5) {
                filter->setAttack(direction);
            } else if (knob == 6) {
                filter->setDecay(direction);
            } else if (knob == 7) {
                filter->setSustain(direction);
            } else if (knob == 8) {
                filter->setRelease(direction);
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
