#ifndef IO_AUDIO_SYNTH_CORE_UI_H_
#define IO_AUDIO_SYNTH_CORE_UI_H_

#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <Audio.h>

#include "../io_display_util.h"
#include "../io_midi_util.h"
#include "../io_state.h"
#include "./io_audio_synth_core.h"
#include "./io_display_helper.h"

class IO_AudioSynthCoreUI {
   private:
    IO_AudioSynthCore* core;

   public:
    IO_AudioSynthCoreUI(IO_AudioSynthCore* _core) { core = _core; }

    void display(Adafruit_SSD1306* d) {
        addToCursor(d, 0, 4);
        if (core->wave.isWaveForm()) {
            d->printf("%s\n", getWave(core->wave.currentWave));
        } else {
            d->printf("%s %s\n", core->wave.isWaveArbitrary() ? "Abr" : "Tbl",
                      core->wave.waveName);
        }

        d->printf("Frequency %.1fHz\n", core->wave.frequency);
        d->printf("Amplitude %d%%\n", (int)(core->wave.amplitude * 100.0));
        if (core->wave.isWaveTable()) {
            d->printf("Start pos %d\n", core->wave.waveTable.start);
        }

        addToCursor(d, 0, 4);
        if (core->isDrum) {
            d->printf("AD %d|%d\n", (int)core->adsr[0], (int)core->adsr[1]);
        } else {
            d->printf("ADSR %d|%d|%d%%|%d\n", (int)core->adsr[0],
                      (int)core->adsr[1], (int)(core->adsr[2] * 100.0),
                      (int)core->adsr[3]);
        }
    }

    void noteOnHandler(byte channel, byte note, byte velocity) {
        if (note == 17 || note == 41) {
            core->toggleDrum();
        }
    }

    void noteOffHandler(byte channel, byte note, byte velocity) {}

    void controlChangeHandler(byte channel, byte knob, int8_t direction) {
        if (channel == 11) {
            if (knob == 1) {
                if (mcMode) {
                } else {
                    core->wave.setNextWaveform(direction);
                }
            } else if (knob == 2) {
                if (mcMode) {
                } else {
                    core->wave.setFrequency(direction);
                }
            } else if (knob == 3) {
                if (mcMode) {
                } else {
                    core->wave.setAmplitude(direction);
                }
            } else if (knob == 4) {
                if (mcMode) {
                } else {
                }
            } else if (knob == 5) {
                if (mcMode) {
                } else {
                    core->setAttack(direction);
                }
            } else if (knob == 6) {
                if (mcMode) {
                } else {
                    core->setDecay(direction);
                }
            } else if (knob == 7) {
                if (mcMode) {
                } else {
                    core->setSustain(direction);
                }
            } else if (knob == 8) {
                if (mcMode) {
                } else {
                    core->setRelease(direction);
                }
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
