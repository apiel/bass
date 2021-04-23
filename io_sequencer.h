#ifndef IO_SEQUENCER_H_
#define IO_SEQUENCER_H_

#include <Arduino.h>
#include <Metro.h>

#include "io_audio.h"

// 4 ♬ ♬ step per beat
#define STEP_PER_BEAT 4

byte bpm = 100;
unsigned int tempo = 150;
Metro timer = Metro(tempo);

void setTempo(int8_t direction) {
    bpm = constrain(bpm + direction, 10, 255);
    // 4 ♬ ♬ step per beat in 60000ms = 1min
    tempo = 60000 / (bpm * STEP_PER_BEAT);
    timer.interval(tempo);
}

void sequencerInit() { setTempo(0); }

void sequencerLoop() {
    if (timer.check() == 1) {
        timer.reset();
        for (byte pos = 0; pos < SYNTH_COUNT; pos++) {
            synth[pos].seq->next();
        }
        for (byte pos = 0; pos < KICK_COUNT; pos++) {
            kick[pos].seq->next();
        }
    }
}

#endif
