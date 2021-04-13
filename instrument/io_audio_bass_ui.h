#ifndef IO_AUDIO_BASS_UI_H_
#define IO_AUDIO_BASS_UI_H_

#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <Audio.h>

#include "../io_display_util.h"
#include "../io_midi_util.h"
#include "../io_state.h"
#include "io_audio_bass.h"
#include "io_display_helper.h"

class IO_AudioBassUI : public IO_AudioBass {
   public:
    void display(Adafruit_SSD1306* d) {
        d->clearDisplay();
        d->setCursor(0, 0);

        d->printf("%s\n", getWave(currentWave[0]));
        d->printf("%.1fHz %d%%\n", frequency[0], (int)(amplitude[0] * 100.0));
        d->printf("%d|%d|%d%%|%d\n", (int)adsr[0][0], (int)adsr[0][1],
                  (int)(adsr[0][2] * 100.0), (int)adsr[0][3]);

        d->printf("%s\n", getWave(currentWave[1]));
        d->printf("%.1fHz %d%%\n", frequency[1], (int)(amplitude[1] * 100.0));
        d->printf("%d|%d|%d%%|%d\n", (int)adsr[1][0], (int)adsr[1][1],
                  (int)(adsr[1][2] * 100.0), (int)adsr[1][3]);

        // if (mcMode) {
        //     if (modulationOn) {
        //         addToCursor(d, 0, 4);
        //         d->println("Modulation level");
        //         d->printf("%.2f|%.2f|%.2f|%.2f\n", modLevel[0], modLevel[1],
        //                   modLevel[2], modLevel[3]);
        //         d->printf("%.2f|%.2f|%.2f|%.2f\n", modLevel[4], modLevel[5],
        //                   modLevel[6], modLevel[7]);

        //         addToCursor(d, 0, 4);
        //         d->println("Modulation ms");
        //         d->printf("%d|%d|%d|%d\n", (int)modMs[0], (int)modMs[1],
        //                   (int)modMs[2], (int)modMs[3]);
        //         d->printf("%d|%d|%d|%d\n", (int)modMs[4], (int)modMs[5],
        //                   (int)modMs[6], (int)modMs[7]);
        //     } else {
        //         d->println("\nNo modulation");
        //     }
        // } else {
        //     d->printf("%.1fHz %d%%\n", waveform.frequency,
        //               (int)(waveform.amplitude * 100));

        //     d->printf("Start %d EG %d|%d\n", waveform.getStart(),
        //     (int)attackMs,
        //               (int)decayMs);

        //     addToCursor(d, 0, 4);
        //     d->printf("%s %.1fHz %.1f\n", getFilter(currentFilter),
        //               filterFrequency, filterResonance);

        //     d->printf("Dist %d range %d\n", (int)distortion.amount,
        //               (int)distortion.range);
        //     d->printf("Bitcrusher %d\n", (int)xcrushBits);

        //     d->printf("%s %s\n", modulationOn ? "ModON" : "ModOFF",
        //               rectifierOn ? "RectON" : "RectOFF");
        // }
    }

    void noteOnHandler(byte channel, byte note, byte velocity) {
        if (channel == 11) {
            byte key = getItemKey(note);
            if (key != 255) {
                // currentkick = key;
            } else if (note == 22 || note == 46) {
                noteOn();
            } else if (note == 23 || note == 47) {
                // savekick(currentkick);
            } else if (note == 20) {
            } else if (note == 17 || note == 41) {
                // if (mcMode) {
                //     toggleModulation();
                // } else {
                //     toggleRectifier();
                // }
            }
        }
    }

    void noteOffHandler(byte channel, byte note, byte velocity) {
        if (channel == 11) {
            if (note == 22 || note == 46) {
                noteOff();
            }
        }
    }

    void controlChangeHandler(byte channel, byte knob, int8_t direction) {
        if (channel == 11) {
            if (knob == 1) {
                if (mcMode) {
                    setCurrentFilter(direction);
                } else {
                    setNextWave(0, direction);
                }
            } else if (knob == 2) {
                if (mcMode) {
                    setFilterFrequency(direction);
                } else {
                    setFrequency(0, direction);
                }
            } else if (knob == 3) {
                if (mcMode) {
                    setFilterResonance(direction);
                } else {
                    setAmplitude(0, direction);
                }
            } else if (knob == 4) {
                if (mcMode) {
                } else {
                }
            } else if (knob == 5) {
                if (mcMode) {
                } else {
                    setAttack(0, direction);
                }
            } else if (knob == 6) {
                if (mcMode) {
                } else {
                    setDecay(0, direction);
                }
            } else if (knob == 7) {
                if (mcMode) {
                    setDistortion(direction);
                } else {
                    setSustain(0, direction);
                }
            } else if (knob == 8) {
                if (mcMode) {
                    setDistortionRange(direction);
                } else {
                    setRelease(0, direction);
                }
            } else if (knob == 11) {
                if (mcMode) {
                } else {
                    setNextWave(1, direction);
                }
            } else if (knob == 12) {
                if (mcMode) {
                } else {
                    setFrequency(1, direction);
                }
            } else if (knob == 13) {
                if (mcMode) {
                } else {
                    setAmplitude(1, direction);
                }
            } else if (knob == 14) {
                if (mcMode) {
                } else {
                }
            } else if (knob == 15) {
                if (mcMode) {
                } else {
                    setAttack(1, direction);
                }
            } else if (knob == 16) {
                if (mcMode) {
                } else {
                    setDecay(1, direction);
                }
            } else if (knob == 17) {
                if (mcMode) {
                } else {
                    setSustain(1, direction);
                }
            } else if (knob == 0) {  // 0 for 18
                if (mcMode) {
                } else {
                    setRelease(1, direction);
                }
            }
        }
    }
};

#endif
