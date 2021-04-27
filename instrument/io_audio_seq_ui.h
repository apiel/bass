#ifndef IO_AUDIO_SEQ_UI_H_
#define IO_AUDIO_SEQ_UI_H_

#include <Adafruit_SSD1306.h>
#include <Arduino.h>

#include "../io_display_util.h"
#include "../io_midi_core.h"
#include "./io_audio_seq.h"
#include "io_config.h"

class IO_AudioSeqUI {
   private:
    IO_AudioSeq* seq;

    void displayStep(Adafruit_SSD1306* d, Pattern* pPattern, byte pos) {
        byte topMargin = 26;
        byte x = pos % 8;
        byte y = pos / 8 + 1;

        Step* step = &pPattern->steps[pos];

        d->drawLine(x * 16 + 1, y * 7 + 7 + topMargin, x * 16 + 12,
                    y * 7 + 7 + topMargin, WHITE);
        if (step->duration) {
            d->setCursor(x * 16 + 2, y * 7 + 5 + topMargin);
            d->printf("%s%d", getNoteDot(step->note),
                      getNoteOctave(step->note));

            if (step->tie) {
                d->drawLine(x * 16 + 12, y * 7 + 3 + topMargin, x * 16 + 12,
                            y * 7 + 7 + topMargin, WHITE);
            }
        }

        if (seq->currentStepSelection == pos) {
            d->drawLine(x * 16 + 2, y * 7 + 6 + topMargin, x * 16 + 10,
                        y * 7 + 6 + topMargin, WHITE);
        }

        if (mcMode && x == 7 && seq->currentRow == pos / 8) {
            d->drawLine(x * 16 + 14, y * 7 + topMargin, x * 16 + 14,
                        y * 7 + 7 + topMargin, WHITE);
        }
    }

   public:
    IO_AudioSeqUI(IO_AudioSeq* _seq) { seq = _seq; }

    void displayPlayingStatus(Adafruit_SSD1306* d) {
        if (seq->active) {
            d->fillTriangle(120, 0, 126, 3, 120, 7, WHITE);
        } else {
            d->fillRect(120, 1, 6, 6, WHITE);
        }
    }

    void display(Adafruit_SSD1306* d) {
        d->printf("%03d %s\n", seq->currentPattern, seq->pattern->name);

        Step* step = &seq->pattern->steps[seq->currentStepSelection];
        if (step->duration) {
            d->printf("\n%s%d %03d Tie %d\n", getNoteStr(step->note),
                      getNoteOctave(step->note), step->velocity,
                      step->tie ? 1 : 0);
        } else {
            d->printf("\n-- %03d Tie %d\n", step->velocity, step->tie ? 1 : 0);
        }

        setSmallFont(d);
        for (byte pos = 0; pos < STEP_COUNT; pos++) {
            displayStep(d, seq->pattern, pos);
        }
        resetFont(d);
    }

    void noteOnHandler(byte channel, byte note, byte velocity) {
        if (channel == 11) {
            if (note == 17 || note == 41) {
                if (mcMode) {
                    seq->toggleTie();
                } else {
                    seq->setStepDurationAndTie();
                }
            } else if (note == 8 || note == 32) {
                seq->toggleStep(0);
            } else if (note == 9 || note == 33) {
                seq->toggleStep(1);
            } else if (note == 10 || note == 34) {
                seq->toggleStep(2);
            } else if (note == 11 || note == 35) {
                seq->toggleStep(3);
            } else if (note == 12 || note == 36) {
                seq->toggleStep(4);
            } else if (note == 13 || note == 37) {
                seq->toggleStep(5);
            } else if (note == 14 || note == 38) {
                seq->toggleStep(6);
            } else if (note == 15 || note == 39) {
                seq->toggleStep(7);
            }
        }
    }

    void noteOffHandler(byte channel, byte note, byte velocity) {
        updateMidiController();
    }

    void updateMidiController() {
        if (mcMode) {
            for (byte pos = 0; pos < 8; pos++) {
                Step* step = &seq->pattern->steps[pos + seq->currentRow * 8];
                if (step->duration) {
                    noteOn(8 + pos);
                    noteOn(32 + pos);
                } else {
                    noteOff(8 + pos);
                    noteOff(32 + pos);
                }
            }
        }
    }

    void controlChangeHandler(byte channel, byte knob, int8_t direction) {
        if (channel == 11) {
            if (knob == 1) {
                seq->setCurrentPattern(direction);
            } else if (knob == 2) {
                seq->setCurrentStepSelection(direction);
            } else if (knob == 3) {
                seq->setStepNote(direction);
            } else if (knob == 4) {
                seq->setStepVelocity(direction);
            } else if (knob == 5) {
                if (mcMode) {
                } else {
                }
            } else if (knob == 6) {
                if (mcMode) {
                } else {
                }
            } else if (knob == 7) {
                if (mcMode) {
                } else {
                }
            } else if (knob == 8) {
                seq->setCurrentRow(direction);
            } else if (knob == 11) {
                if (mcMode) {
                } else {
                }
            } else if (knob == 12) {
                if (mcMode) {
                } else {
                }
            } else if (knob == 13) {
                if (mcMode) {
                } else {
                }
            } else if (knob == 14) {
                if (mcMode) {
                } else {
                }
            } else if (knob == 15) {
                if (mcMode) {
                } else {
                }
            } else if (knob == 16) {
                if (mcMode) {
                } else {
                }
            } else if (knob == 17) {
                if (mcMode) {
                } else {
                }
            } else if (knob == 0) {  // 0 for 18
                if (mcMode) {
                } else {
                }
            }
        }
    }
};

#endif
