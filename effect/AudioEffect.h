#ifndef AudioEffect_h_
#define AudioEffect_h_

#include <Arduino.h>
#include <Audio.h>

#include "./AudioEffectDistortion.h"
#include "../audio/audio_dumb.h"

class AudioEffect : public AudioDumb {
   private:
    AudioConnection* patchCordInput;
    AudioConnection* patchCordBitcrusher;
    AudioConnection* patchCordDistortionToRectifier;
    AudioConnection* patchCordDistortionToOutput;
    AudioConnection* patchCordRectifier;

   public:
    AudioDumb input;
    AudioEffectBitcrusher bitcrusher;
    AudioEffectDistortion distortion;
    AudioEffectRectifier rectifier;

    byte xcrushBits = 12;
    bool rectifierOn = false;

    AudioEffect() {
        patchCordInput = new AudioConnection(input, bitcrusher);
        patchCordBitcrusher = new AudioConnection(bitcrusher, distortion);
        patchCordDistortionToRectifier =
            new AudioConnection(distortion, rectifier);
        patchCordDistortionToOutput = new AudioConnection(distortion, *this);
        patchCordRectifier = new AudioConnection(rectifier, *this);

        setBitcrusher(0);
        applyRectifier();
        setDistortion(0);
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
};

#endif
