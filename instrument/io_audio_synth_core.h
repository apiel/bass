#ifndef IO_AUDIO_SYNTH_CORE_H_
#define IO_AUDIO_SYNTH_CORE_H_

#include <Arduino.h>
#include <Audio.h>

#include "../audio/AudioFilter.h"
#include "../audio/AudioModulation.h"
#include "../audio/audio_dumb.h"
#include "../audio/note.h"
#include "../effect/AudioEffectDistortion.h"
#include "../io_util.h"
#include "../wavetable/guitar01.h"
#include "./io_audio_synth_wave.h"

class IO_AudioSynthCore : public AudioDumb {
   protected:
   public:
    IO_AudioSynthWave wave;
    AudioEffectEnvelope env;
    AudioEffectDistortion distortion;
    AudioFilter filter;
    AudioModulation freqMod;

    byte lastNote = 0;

    bool isDrum = false;
    float adsr[4] = {10.0, 50.0, 1.0, 50.0};

    byte currentWave = WAVEFORM_SINE;
    float frequency = 120.0;
    float amplitude = 1.0;

    AudioConnection* patchCordFreqModToWave;
    AudioConnection* patchCordWaveToEnv;
    AudioConnection* patchCordEnvToFilter;
    AudioConnection* patchCordFilterToDistortion;
    AudioConnection* patchCordDistortionToOutput;

    Guitar01 table;

    IO_AudioSynthCore() {
        patchCordFreqModToWave = new AudioConnection(freqMod, wave.input);
        patchCordWaveToEnv = new AudioConnection(wave, env);
        patchCordEnvToFilter = new AudioConnection(env, filter.input);
        patchCordFilterToDistortion = new AudioConnection(filter, distortion);
        patchCordDistortionToOutput = new AudioConnection(distortion, *this);

        env.hold(0);
        env.attack(adsr[0]);
        env.decay(adsr[1]);
        env.sustain(adsr[2]);
        env.release(adsr[3]);

        distortion.distortion(0.5);
    }

    void setDistortion(int8_t direction) {
        float amount = constrain(distortion.amount + direction, 0, 1000);
        distortion.distortion(amount);
    }

    void setDistortionRange(int8_t direction) {
        float range = constrain(distortion.range + direction, 1, 1000);
        distortion.setRange(range);
    }

    void setAttack(int8_t direction) {
        adsr[0] = constrain(adsr[0] + direction, 0.0, 11880.0);
        env.attack(adsr[0]);
    }

    void setDecay(int8_t direction) {
        adsr[1] = constrain(adsr[1] + direction, 0.0, 11880.0);
        env.decay(adsr[1]);
    }

    void setSustain(int8_t direction) {
        if (!isDrum) {
            adsr[2] = pctAdd(adsr[2], direction);
            env.sustain(adsr[2]);
        }
    }

    void setRelease(int8_t direction) {
        if (!isDrum) {
            adsr[3] = constrain(adsr[3] + direction, 0.0, 11880.0);
            env.release(adsr[3]);
        }
    }

    void toggleDrum() {
        isDrum = !isDrum;
        if (isDrum) {
            env.sustain(0.0);
            env.release(0.0);
        } else {
            env.sustain(adsr[2]);
            env.release(adsr[3]);
        }
    }

    void noteOn() { noteOn(_C4, 127); }

    void noteOn(byte note, byte velocity) {
        // lastNote = note;

        // float _freq = waveform.frequency + NOTE_FREQ[note] - NOTE_FREQ[_C4];
        // float _amp = waveform.amplitude * velocity / 127;

        // // this is not ok :p
        // // waveform.setAmplitude(_amp);
        // // waveform.setFrequency(_freq);
        env.noteOn();
        freqMod.env.noteOn();
        filter.env.noteOn();
    }

    void noteOff() { noteOff(_C4); }
    void noteOff(byte note) {
        if (!isDrum) {
            env.noteOff();
            freqMod.env.noteOff();
            filter.env.noteOff();
        }
    }
};

#endif
