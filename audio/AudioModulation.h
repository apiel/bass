#ifndef AudioModulation_h_
#define AudioModulation_h_

#include <Arduino.h>
#include <Audio.h>

#include "../io_util.h"
#include "./audio_dumb.h"
#include "./envelope.h"

#define MOD_ENV_SIZE 8

class AudioModulation : public AudioDumb {
   private:
    AudioSynthWaveformDc dc;

    AudioConnection* patchCordDcToEnv;
    AudioConnection* patchCordOutput;

   public:
    Envelope<8> env;
    bool modulationOn = true;

    float modMs[MOD_ENV_SIZE] = {5.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 5.0};
    float modLevel[MOD_ENV_SIZE] = {1.0, 0.8, 0.6, 0.4, 0.3, 0.2, 0.1, 0.0};

    AudioModulation() {
        patchCordDcToEnv = new AudioConnection(dc, env);
        patchCordOutput = new AudioConnection(env, *this);

        dc.amplitude(0.5);

        for (byte n = 0; n < MOD_ENV_SIZE; n++) {
            env.set(n + 1, modLevel[n], modMs[n]);
        }
    }

    void toggleModulation() {
        modulationOn = !modulationOn;
        applyModulation();
    }

    void applyModulation() {
        if (modulationOn) {
            patchCordDcToEnv->connect();
            patchCordOutput->connect();
        } else {
            patchCordDcToEnv->disconnect();
            patchCordOutput->disconnect();
        }
    }

    void setModMs(byte state, int8_t direction) {
        if (modulationOn) {
            modMs[state] = constrain(modMs[state] + direction, 0.0, 11880.0);
            env.set(state + 1, modLevel[state], modMs[state]);
        }
    }

    void setModLevel(byte state, int8_t direction) {
        if (modulationOn) {
            modLevel[state] =
                constrain(modLevel[state] + direction * 0.01, 0.0, 1.0);
            env.set(state + 1, modLevel[state], modMs[state]);
        }
    }
};

#endif
