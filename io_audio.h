#ifndef IO_AUDIO_H_
#define IO_AUDIO_H_

#include <Arduino.h>
#include <Audio.h>

#include "io_instrument.h"

AudioOutputMQS audioOut;
AudioConnection patchCordSynth(synth[SYNTH_0], audioOut);

void audioInit() {
    AudioMemory(25);
    for (byte pos = 0; pos < SYNTH_COUNT; pos++) {
        synth[pos].init();
    }
}

#endif
