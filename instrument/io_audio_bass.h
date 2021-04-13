#ifndef IO_AUDIO_BASS_H_
#define IO_AUDIO_BASS_H_

#include <Arduino.h>
#include <Audio.h>

#include "../audio/audio_dumb.h"
#include "../audio/note.h"
#include "../wavetable/guitar01.h"
#include "effect/AudioEffectDistortion.h"
#include "io_util.h"

#define WAVEFORM_COUNT 9

#define FILTER_TYPE_COUNT 3
#define AUDIO_SYNTH_MOD 3
#define MOD_ENV_SIZE 8

class IO_AudioBass : public AudioDumb {
   protected:
   public:
    AudioSynthWaveform wave[2];
    AudioEffectEnvelope env[2];
    AudioFilterStateVariable filter;
    AudioEffectDistortion distortion;

    AudioMixer4 mixer;

    byte lastNote = 0;

    float adsr[2][4] = {{10.0, 50.0, 1.0, 50.0}, {10.0, 50.0, 1.0, 50.0}};

    float filterFrequency = 200.0;
    float filterOctaveControl = 1.0;
    float filterResonance = 0.7;
    byte currentFilter = 0;

    byte currentWave[2] = {WAVEFORM_SINE, WAVEFORM_SAWTOOTH};
    float frequency[2] = {220.0, 220.0};
    float amplitude[2] = {1.0, 1.0};

    AudioConnection* patchCordWaveToEnv[2];
    AudioConnection* patchCordEnvToMixer[2];
    AudioConnection* patchCordMixerToFilter;
    AudioConnection* patchCordFilter[FILTER_TYPE_COUNT];
    AudioConnection* patchCordDistortionToOutput;

    Guitar01 table;

    IO_AudioBass() {
        patchCordWaveToEnv[0] = new AudioConnection(wave[0], env[0]);
        patchCordWaveToEnv[1] = new AudioConnection(wave[1], env[1]);
        patchCordEnvToMixer[0] = new AudioConnection(env[0], mixer);
        patchCordEnvToMixer[1] = new AudioConnection(env[1], 0, mixer, 1);
        patchCordMixerToFilter = new AudioConnection(mixer, filter);
        patchCordFilter[0] = new AudioConnection(filter, 0, distortion, 0);
        patchCordFilter[1] = new AudioConnection(filter, 1, distortion, 0);
        patchCordFilter[2] = new AudioConnection(filter, 2, distortion, 0);
        patchCordDistortionToOutput = new AudioConnection(distortion, *this);

        setCurrentFilter(0);
        filter.frequency(filterFrequency);
        filter.resonance(filterResonance);
        filter.octaveControl(filterOctaveControl);

        initWave(0);
        initWave(1);

        distortion.distortion(0.0);
    }

    void initWave(byte i) {
        env[i].hold(0);
        env[i].attack(adsr[i][0]);
        env[i].decay(adsr[i][1]);
        env[i].sustain(adsr[i][2]);
        env[i].release(adsr[i][3]);

        wave[i].frequency(frequency[i]);
        wave[i].amplitude(amplitude[i]);
        wave[i].arbitraryWaveform(table.table, 172.0);
        wave[i].begin(currentWave[i]);
    }

    void init() {}

    void setNextWave(byte n, int8_t direction) {
        currentWave[n] = mod(currentWave[n] + direction, WAVEFORM_COUNT);
        wave[n].begin(currentWave[n]);
    }

    void setFrequency(byte n, int8_t direction) {
        frequency[n] =
            constrain(frequency[n] + direction, 0, AUDIO_SAMPLE_RATE_EXACT / 2);
        wave[n].frequency(frequency[n]);
    }

    void setAmplitude(byte n, int8_t direction) {
        amplitude[n] = pctAdd(amplitude[n], direction);
        wave[n].amplitude(amplitude[n]);
    }

    void setDistortion(int8_t direction) {
        float amount = constrain(distortion.amount + direction, 0, 1000);
        distortion.distortion(amount);
    }

    void setDistortionRange(int8_t direction) {
        float range = constrain(distortion.range + direction, 1, 1000);
        distortion.setRange(range);
    }

    void setCurrentFilter(int8_t direction) {
        currentFilter = mod(currentFilter + direction, FILTER_TYPE_COUNT);
        // as only the last connected is the one used
        // https://www.pjrc.com/teensy/td_libs_AudioConnection.html
        patchCordFilter[currentFilter]->connect();
    }

    void setFilterFrequency(int8_t direction) {
        filterFrequency = constrain(filterFrequency + direction, 0,
                                    AUDIO_SAMPLE_RATE_EXACT / 2);
        filter.frequency(filterFrequency);
    }

    void setFilterResonance(int8_t direction) {
        filterResonance =
            constrain(filterResonance + direction * 0.1, 0.7, 5.0);
        filter.resonance(filterResonance);
    }

    void setFilterOctaveControl(int8_t direction) {
        filterOctaveControl =
            constrain(filterOctaveControl + direction * 0.1, 0.0, 7.0);
        filter.octaveControl(filterOctaveControl);
    }

    void setAttack(byte n, int8_t direction) {
        adsr[n][0] = constrain(adsr[n][0] + direction, 0.0, 11880.0);
        env[n].attack(adsr[n][0]);
    }

    void setDecay(byte n, int8_t direction) {
        adsr[n][1] = constrain(adsr[n][1] + direction, 0.0, 11880.0);
        env[n].decay(adsr[n][1]);
    }

    void setSustain(byte n, int8_t direction) {
        adsr[n][2] = constrain(adsr[n][2] + direction, 0.0, 1.0);
        env[n].sustain(adsr[n][2]);
    }

    void setRelease(byte n, int8_t direction) {
        adsr[n][3] = constrain(adsr[n][3] + direction, 0.0, 11880.0);
        env[n].release(adsr[n][3]);
    }

    void noteOn() { noteOn(_C4, 127); }

    void noteOn(byte note, byte velocity) {
        // lastNote = note;

        // float _freq = waveform.frequency + NOTE_FREQ[note] - NOTE_FREQ[_C4];
        // float _amp = waveform.amplitude * velocity / 127;

        // // this is not ok :p
        // // waveform.setAmplitude(_amp);
        // // waveform.setFrequency(_freq);
        env[0].noteOn();
        env[1].noteOn();
    }

    void noteOff() { noteOff(_C4); }
    void noteOff(byte note) {
        env[0].noteOff();
        env[1].noteOff();
    }
};

#endif
