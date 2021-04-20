#ifndef IO_AUDIO_SYNTH_SEQ_UI_H_
#define IO_AUDIO_SYNTH_SEQ_UI_H_

#include <Adafruit_SSD1306.h>
#include <Arduino.h>

#include "../../io_display_util.h"
#include "./io_audio_synth_core.h"
#include "./io_audio_synth_seq.h"
#include "io_config.h"

class IO_AudioSynthSeqUI {
   private:
    IO_AudioSynthCore* core;
    IO_AudioSynthSeq* seq;

    void displayStep(Adafruit_SSD1306* d, Pattern* pPattern, byte pos) {
        byte topMargin = 18;
        byte x = pos % 8;
        byte y = pos / 8 + 1;

        Step* step = &pPattern->steps[pos];

        d->drawLine(x * 16 + 1, y * 7 + 7 + topMargin, x * 16 + 12,
                    y * 7 + 7 + topMargin, WHITE);
        if (step->duration) {
            d->setCursor(x * 16 + 2, y * 7 + 5 + topMargin);
            d->printf("%s%d", getNoteDot(step->note),
                      getNoteOctave(step->note));

            // this show the duration but will be buggy when note go on the next
            // line need to think about a solution
            for (byte duration = 1; duration < step->duration; duration++) {
                d->drawLine(duration * (x + 1) * 16 - 4, y * 7 + 6 + topMargin,
                            duration * (x + 1) * 16 - 4 + 5,
                            y * 7 + 6 + topMargin, WHITE);
            }
        }

        if (seq->currentStepSelection == pos) {
            d->drawLine(x * 16 + 2, y * 7 + 6 + topMargin, x * 16 + 10,
                        y * 7 + 6 + topMargin, WHITE);
        }
    }

   public:
    IO_AudioSynthSeqUI(IO_AudioSynthCore* _core, IO_AudioSynthSeq* _seq) {
        core = _core;
        seq = _seq;
    }

    void display(Adafruit_SSD1306* d) {
        d->clearDisplay();
        d->setCursor(0, 0);

        d->printf("%03d %s\n", seq->currentPattern, seq->pattern->name);

        Step* step = &seq->pattern->steps[seq->currentStepSelection];
        d->printf("\nD: %d V: %03d S: %d\n", step->duration, step->velocity,
                  step->slide ? 1 : 0);

        setSmallFont(d);
        for (byte pos = 0; pos < STEP_COUNT; pos++) {
            displayStep(d, seq->pattern, pos);
        }
        resetFont(d);
    }

    void noteOnHandler(byte channel, byte note, byte velocity) {
        if (channel == 11) {
            if (note == 22 || note == 46) {
                seq->toggle();
            }
        }
    }
};

#endif
