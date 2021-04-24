#ifndef IO_AUDIO_KICK_CORE_H_
#define IO_AUDIO_KICK_CORE_H_

#include <Arduino.h>
#include <Audio.h>

#include "../../audio/AudioFilter.h"
#include "../../audio/audio_dumb.h"
#include "../../audio/envelope.h"
#include "../../audio/note.h"
#include "../../effect/AudioEffectDistortion.h"
#include "../../io_util.h"
#include "../../wavetable/kick06.h"
#include "../io_audio_synth_wave.h"

#define KICK_FILTER_TYPE_COUNT 3
#define AUDIO_SYNTH_MOD 3
#define MOD_ENV_SIZE 8

class IO_AudioKickCore : public AudioDumb {
   protected:
   public:
    IO_AudioSynthWave waveform;
    Envelope<2> env;
    AudioFilter filter;
    AudioSynthWaveformDc dc;
    Envelope<8> envMod;
    AudioEffectBitcrusher bitcrusher;
    AudioEffectDistortion distortion;
    AudioEffectRectifier rectifier;

    bool modulationOn = true;

    float attackMs = 10.0;
    float decayMs = 240.0;

    float modMs[MOD_ENV_SIZE] = {5.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 5.0};
    float modLevel[MOD_ENV_SIZE] = {1.0, 0.8, 0.6, 0.4, 0.3, 0.2, 0.1, 0.0};

    float filterFrequency = 200.0;
    float filterOctaveControl = 1.0;
    float filterResonance = 0.7;
    byte currentFilter = 0;

    byte xcrushBits = 12;
    bool rectifierOn = false;

    AudioConnection* patchCordFilter;
    AudioConnection* patchCordEnvToFilter;
    AudioConnection* patchCordWaveToEnv;
    AudioConnection* patchCordDcToEnvMod;
    AudioConnection* patchCordEnvModToWave;
    AudioConnection* patchCordBitcrusher;
    AudioConnection* patchCordDistortionToRectifier;
    AudioConnection* patchCordDistortionToOutput;
    AudioConnection* patchCordRectifier;

    IO_AudioKickCore() {
        patchCordDcToEnvMod = new AudioConnection(dc, envMod);
        patchCordEnvModToWave = new AudioConnection(envMod, waveform.input);
        patchCordWaveToEnv = new AudioConnection(waveform, env);
        patchCordEnvToFilter = new AudioConnection(env, filter.input);
        patchCordFilter = new AudioConnection(filter, bitcrusher);
        patchCordBitcrusher = new AudioConnection(bitcrusher, distortion);
        patchCordDistortionToRectifier =
            new AudioConnection(distortion, rectifier);
        patchCordDistortionToOutput = new AudioConnection(distortion, *this);
        patchCordRectifier = new AudioConnection(rectifier, *this);

        env.set(1, 1.0, attackMs);
        env.set(2, 0.0, decayMs);

        dc.amplitude(0.5);

        for (byte n = 0; n < MOD_ENV_SIZE; n++) {
            envMod.set(n + 1, modLevel[n], modMs[n]);
        }

        setBitcrusher(0);
        applyRectifier();
        applyModulation();
    }

    void toggleRectifier() {
        rectifierOn = !rectifierOn;
        applyRectifier();
    }

    void applyRectifier() {
        patchCordDistortionToRectifier->disconnect();
        patchCordDistortionToOutput->disconnect();
        patchCordRectifier->disconnect();
        if (rectifierOn) {
            patchCordDistortionToRectifier->connect();
            patchCordRectifier->connect();
        } else {
            patchCordDistortionToOutput->connect();
        }
    }

    void toggleModulation() {
        modulationOn = !modulationOn;
        applyModulation();
    }

    void applyModulation() {
        if (modulationOn) {
            patchCordDcToEnvMod->connect();
            patchCordEnvModToWave->connect();
        } else {
            patchCordDcToEnvMod->disconnect();
            patchCordEnvModToWave->disconnect();
        }
    }

    void setBitcrusher(int8_t direction) {
        xcrushBits = constrain(xcrushBits + direction, 1, 16);
        bitcrusher.bits(xcrushBits);
    }

    void setDistortion(int8_t direction) {
        float amount = constrain(distortion.amount + direction, 0, 1000);
        distortion.distortion(amount);
    }

    void setDistortionRange(int8_t direction) {
        float range = constrain(distortion.range + direction, 1, 1000);
        distortion.setRange(range);
    }

    void setModMs(byte state, int8_t direction) {
        if (modulationOn) {
            modMs[state] = constrain(modMs[state] + direction, 0.0, 11880.0);
            envMod.set(state + 1, modLevel[state], modMs[state]);
        }
    }

    void setModLevel(byte state, int8_t direction) {
        if (modulationOn) {
            modLevel[state] =
                constrain(modLevel[state] + direction * 0.01, 0.0, 1.0);
            envMod.set(state + 1, modLevel[state], modMs[state]);
        }
    }

    void setAttack(int8_t direction) {
        attackMs = constrain(attackMs + direction, 0, 11880);
        // env.attack(attackMs);
        env.set(1, 1.0, attackMs);
    }

    void setDecay(int8_t direction) {
        decayMs = constrain(decayMs + direction, 0, 11880);
        // env.decay(decayMs);
        env.set(2, 0.0, decayMs);
    }

    void noteOn() { noteOn(_C4, 127); }

    void noteOn(byte note, byte velocity) {
        envMod.noteOn();
        env.noteOn();
        filter.env.noteOn();
    }

    void noteOff() {}
    void noteOff(byte note) {}
};

#endif
