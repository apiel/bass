#ifndef IO_AUDIO_SYNTH_KICK_UI_H_
#define IO_AUDIO_SYNTH_KICK_UI_H_

#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <Audio.h>

#include "../../io_display_util.h"
#include "../../io_midi_util.h"
#include "../../io_state.h"
#include "../io_display_helper.h"
#include "./io_audio_kick_core.h"

class IO_AudioKickCoreUI {
   private:
    IO_AudioKickCore* core;

   public:
    IO_AudioKickCoreUI(IO_AudioKickCore* _core) { core = _core; }

    void display(Adafruit_SSD1306* d) {
        d->clearDisplay();
        d->setCursor(0, 0);

        d->printf("%s %s\n", core->waveform.isWaveForm() ? "#" : "~",
                  core->waveform.waveName);

        if (mcMode) {
            if (core->modulationOn) {
                addToCursor(d, 0, 4);
                d->println("Modulation level");
                d->printf("%.2f|%.2f|%.2f|%.2f\n", core->modLevel[0],
                          core->modLevel[1], core->modLevel[2],
                          core->modLevel[3]);
                d->printf("%.2f|%.2f|%.2f|%.2f\n", core->modLevel[4],
                          core->modLevel[5], core->modLevel[6],
                          core->modLevel[7]);

                addToCursor(d, 0, 4);
                d->println("Modulation ms");
                d->printf("%d|%d|%d|%d\n", (int)core->modMs[0],
                          (int)core->modMs[1], (int)core->modMs[2],
                          (int)core->modMs[3]);
                d->printf("%d|%d|%d|%d\n", (int)core->modMs[4],
                          (int)core->modMs[5], (int)core->modMs[6],
                          (int)core->modMs[7]);
            } else {
                d->println("\nNo modulation");
            }
        } else {
            d->printf("%.1fHz %d%%\n", core->waveform.frequency,
                      (int)(core->waveform.amplitude * 100));

            d->printf("Start %d EG %d|%d\n", core->waveform.getStart(),
                      (int)core->attackMs, (int)core->decayMs);

            addToCursor(d, 0, 4);
            d->printf("%s %.1fHz %.1f\n", getFilter(core->currentFilter),
                      core->filterFrequency, core->filterResonance);

            d->printf("Dist %d range %d\n", (int)core->distortion.amount,
                      (int)core->distortion.range);
            d->printf("Bitcrusher %d\n", (int)core->xcrushBits);

            d->printf("%s %s\n", core->modulationOn ? "ModON" : "ModOFF",
                      core->rectifierOn ? "RectON" : "RectOFF");
        }
    }

    void noteOnHandler(byte channel, byte note, byte velocity) {
        if (channel == 11) {
            byte key = getItemKey(note);
            if (key != 255) {
                // currentkick = key;
            } else if (note == 21 || note == 45) {
                core->noteOn();
            } else if (note == 23 || note == 47) {
                // savekick(currentkick);
            } else if (note == 20) {
            } else if (note == 17 || note == 41) {
                if (mcMode) {
                    core->toggleModulation();
                } else {
                    core->toggleRectifier();
                }
            }
        }
    }

    void noteOffHandler(byte channel, byte note, byte velocity) {
        if (channel == 11) {
            if (note == 22 || note == 46) {
                core->noteOff();
            }
        }
    }

    void controlChangeHandler(byte channel, byte knob, int8_t direction) {
        if (channel == 11) {
            if (knob == 1) {
                if (mcMode) {
                    core->setModLevel(0, direction);
                } else {
                    core->waveform.setNextWaveform(direction);
                }
            } else if (knob == 2) {
                if (mcMode) {
                    core->setModLevel(1, direction);
                } else {
                    core->waveform.setFrequency(direction);
                }
            } else if (knob == 3) {
                if (mcMode) {
                    core->setModLevel(2, direction);
                } else {
                    core->waveform.setAmplitude(direction);
                }
            } else if (knob == 4) {
                if (mcMode) {
                    core->setModLevel(3, direction);
                } else {
                }
            } else if (knob == 5) {
                if (mcMode) {
                    core->setModLevel(4, direction);
                } else {
                }
            } else if (knob == 6) {
                if (mcMode) {
                    core->setModLevel(5, direction);
                } else {
                    core->waveform.setStart(direction);
                }
            } else if (knob == 7) {
                if (mcMode) {
                    core->setModLevel(6, direction);
                } else {
                    core->setAttack(direction);
                }
            } else if (knob == 8) {
                if (mcMode) {
                    core->setModLevel(7, direction);
                } else {
                    core->setDecay(direction);
                }
            } else if (knob == 11) {
                if (mcMode) {
                    core->setModMs(0, direction);
                } else {
                    core->setCurrentFilter(direction);
                }
            } else if (knob == 12) {
                if (mcMode) {
                    core->setModMs(1, direction);
                } else {
                    core->setFilterFrequency(direction);
                }
            } else if (knob == 13) {
                if (mcMode) {
                    core->setModMs(2, direction);
                } else {
                    core->setFilterResonance(direction);
                }
            } else if (knob == 14) {
                if (mcMode) {
                    core->setModMs(3, direction);
                } else {
                }
            } else if (knob == 15) {
                if (mcMode) {
                    core->setModMs(4, direction);
                } else {
                }
            } else if (knob == 16) {
                if (mcMode) {
                    core->setModMs(5, direction);
                } else {
                    core->setDistortion(direction);
                }
            } else if (knob == 17) {
                if (mcMode) {
                    core->setModMs(6, direction);
                } else {
                    core->setDistortionRange(direction);
                }
            } else if (knob == 0) {  // 0 for 18
                if (mcMode) {
                    core->setModMs(7, direction);
                } else {
                    core->setBitcrusher(direction);
                }
            }
        }
    }
};

#endif
