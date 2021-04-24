#ifndef IO_AUDIO_H_
#define IO_AUDIO_H_

#include <Arduino.h>
#include <Audio.h>

#include "io_instrument.h"

AudioOutputMQS audioOut;
AudioMixer4 mixerSynth;
// AudioMixer4 mixerKick;

AudioConnection patchCordMixerSynth(mixerSynth, audioOut);
// AudioConnection patchCordMixerSynth(mixerSynth, 0, mixerKick, 3);
AudioConnection patchCordSynth0(synth[SYNTH_0], mixerSynth);
AudioConnection patchCordSynth1(synth[SYNTH_1], 0, mixerSynth, 1);
AudioConnection patchCordSynth2(synth[SYNTH_2], 0, mixerSynth, 2);
AudioConnection patchCordSynth3(synth[SYNTH_3], 0, mixerSynth, 3);

// AudioConnection patchCordMixerKick(mixerKick, audioOut);
// AudioConnection patchCordKick0(kick[KICK_0], mixerKick);
// AudioConnection patchCordkick1(kick[KICK_1], 0, mixerKick, 1);

void audioInit() {
    AudioMemory(25);
    for (byte pos = 0; pos < SYNTH_COUNT; pos++) {
        synth[pos].init();
    }
    // for (byte pos = 0; pos < KICK_COUNT; pos++) {
    //     kick[pos].init();
    // }
}

#endif
