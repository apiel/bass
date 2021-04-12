#ifndef IO_AUDIO_BASS_DISPLAY_H_
#define IO_AUDIO_BASS_DISPLAY_H_

#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <Audio.h>

#include "../io_display_util.h"
#include "../io_state.h"
#include "io_audio_bass.h"
#include "io_display_helper.h"

class IO_AudioBassDisplay : public IO_AudioBass {
   public:
    void display(Adafruit_SSD1306* d) {
        d->clearDisplay();
        d->setCursor(0, 0);

        d->printf("%s %s\n", waveform.isWave256() ? "#" : "~",
                  waveform.waveName);

        if (mcMode) {
            if (modulationOn) {
                addToCursor(d, 0, 4);
                d->println("Modulation level");
                d->printf("%.2f|%.2f|%.2f|%.2f\n", modLevel[0], modLevel[1],
                          modLevel[2], modLevel[3]);
                d->printf("%.2f|%.2f|%.2f|%.2f\n", modLevel[4], modLevel[5],
                          modLevel[6], modLevel[7]);

                addToCursor(d, 0, 4);
                d->println("Modulation ms");
                d->printf("%d|%d|%d|%d\n", (int)modMs[0], (int)modMs[1],
                          (int)modMs[2], (int)modMs[3]);
                d->printf("%d|%d|%d|%d\n", (int)modMs[4], (int)modMs[5],
                          (int)modMs[6], (int)modMs[7]);
            } else {
                d->println("\nNo modulation");
            }
        } else {
            d->printf("%.1fHz %d%%\n", waveform.frequency,
                      (int)(waveform.amplitude * 100));

            d->printf("Start %d EG %d|%d\n", waveform.getStart(), (int)attackMs,
                      (int)decayMs);

            addToCursor(d, 0, 4);
            d->printf("%s %.1fHz %.1f\n", getFilter(currentFilter),
                      filterFrequency, filterResonance);

            d->printf("Dist %d range %d\n", (int)distortion.amount,
                      (int)distortion.range);
            d->printf("Bitcrusher %d\n", (int)xcrushBits);

            d->printf("%s %s\n", modulationOn ? "ModON" : "ModOFF",
                      rectifierOn ? "RectON" : "RectOFF");
        }
    }
};

#endif
