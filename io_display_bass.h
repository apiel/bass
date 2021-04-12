#ifndef IO_DISPLAY_KICK_H_
#define IO_DISPLAY_KICK_H_

#include <Adafruit_SSD1306.h>

#include "io_display.h"
#include "io_display_util.h"
#include "io_state.h"

const char* getFilter(byte w) {
    switch (w) {
        case 0:
            return "LowP";
        case 1:
            return "BandP";
        case 2:
            return "HighP";
    }
    return "??";
}

void displayKick(Adafruit_SSD1306* d) {
    d->clearDisplay();
    d->setCursor(0, 0);

    d->printf("%s %s\n", bass.waveform.isWave256() ? "#" : "~",
              bass.waveform.waveName);

    if (mcMode) {
        if (bass.modulationOn) {
            addToCursor(d, 0, 4);
            d->println("Modulation level");
            d->printf("%.2f|%.2f|%.2f|%.2f\n", bass.modLevel[0],
                      bass.modLevel[1], bass.modLevel[2], bass.modLevel[3]);
            d->printf("%.2f|%.2f|%.2f|%.2f\n", bass.modLevel[4],
                      bass.modLevel[5], bass.modLevel[6], bass.modLevel[7]);

            addToCursor(d, 0, 4);
            d->println("Modulation ms");
            d->printf("%d|%d|%d|%d\n", (int)bass.modMs[0], (int)bass.modMs[1],
                      (int)bass.modMs[2], (int)bass.modMs[3]);
            d->printf("%d|%d|%d|%d\n", (int)bass.modMs[4], (int)bass.modMs[5],
                      (int)bass.modMs[6], (int)bass.modMs[7]);
        } else {
            d->println("\nNo modulation");
        }
    } else {
        d->printf("%.1fHz %d%%\n", bass.waveform.frequency,
                  (int)(bass.waveform.amplitude * 100));

        d->printf("Start %d EG %d|%d\n", bass.waveform.getStart(),
                  (int)bass.attackMs, (int)bass.decayMs);

        addToCursor(d, 0, 4);
        d->printf("%s %.1fHz %.1f\n", getFilter(bass.currentFilter),
                  bass.filterFrequency, bass.filterResonance);

        d->printf("Dist %d range %d\n", (int)bass.distortion.amount,
                  (int)bass.distortion.range);
        d->printf("Bitcrusher %d\n", (int)bass.xcrushBits);

        d->printf("%s %s\n", bass.modulationOn ? "ModON" : "ModOFF",
                  bass.rectifierOn ? "RectON" : "RectOFF");
    }
}

#endif
