#ifndef IO_AUDIO_H_
#define IO_AUDIO_H_

#include <Arduino.h>
#include <Audio.h>

#include "io_instrument.h"

AudioOutputMQS audioOut;
AudioConnection patchCordSynth(synth, audioOut);

void audioInit() {
    AudioMemory(25);
    synth.init();
}

#endif
