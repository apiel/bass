#ifndef IO_MIDI_CORE_H_
#define IO_MIDI_CORE_H_

#include <Arduino.h>
#include <USBHost_t36.h>

#define MIDI_COUNT 4

USBHost myusb;
USBHub hub1(myusb);
USBHub hub2(myusb);
USBHub hub3(myusb);
MIDIDevice midi[MIDI_COUNT] = MIDIDevice(myusb);

void noteOn(uint8_t note, uint8_t velocity, uint8_t channel) {
    for (byte n = 0; n < MIDI_COUNT; n++) {
        midi[n].sendNoteOn(note, velocity, channel);
    }
}
void noteOn(uint8_t note) { noteOn(note, 100, 11); }

void noteOff(uint8_t note, uint8_t velocity, uint8_t channel) {
    for (byte n = 0; n < MIDI_COUNT; n++) {
        midi[n].sendNoteOff(note, velocity, channel);
    }
}
void noteOff(uint8_t note) { noteOff(note, 100, 11); }

#endif
