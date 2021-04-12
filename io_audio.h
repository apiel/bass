#ifndef IO_AUDIO_H_
#define IO_AUDIO_H_

#include <Arduino.h>
#include <Audio.h>

#include "instrument/io_audio_bass.h"
#include "io_instrument.h"

AudioOutputMQS audioOut;
AudioConnection patchCordBass(bass, audioOut);

void audioInit() {
    AudioMemory(25);
    bass.init();
}

#endif
