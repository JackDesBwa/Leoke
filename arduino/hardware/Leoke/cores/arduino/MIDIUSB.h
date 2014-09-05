#include "USBDesc.h"

#if defined(USBCON)
#ifdef MIDI_ENABLED

#ifndef MIDIUSB_H
#define MIDIUSB_H

// Midi notes
enum MidiNote {
  MidiNote_C,  MidiNote_Cs,
  MidiNote_D,  MidiNote_Ds,
  MidiNote_E,
  MidiNote_F,  MidiNote_Fs,
  MidiNote_G,  MidiNote_Gs,
  MidiNote_A,  MidiNote_As,
  MidiNote_B
};

// Midi octaves
enum MidiOctave {
  MidiOctave_m1 = 0,
  MidiOctave_0 = 12,
  MidiOctave_1 = 24,
  MidiOctave_2 = 36,
  MidiOctave_3 = 48,
  MidiOctave_4 = 60,
  MidiOctave_5 = 72,
  MidiOctave_6 = 84,
  MidiOctave_7 = 96,
  MidiOctave_8 = 108,
  MidiOctave_9 = 120
};

// Midi channels
enum MidiChannel {
  MidiChannel_1,  MidiChannel_2,   MidiChannel_3,  MidiChannel_4,
  MidiChannel_5,  MidiChannel_6,   MidiChannel_7,  MidiChannel_8,
  MidiChannel_9,  MidiChannel_10,  MidiChannel_11, MidiChannel_12,
  MidiChannel_13, MidiChannel_14,  MidiChannel_15, MidiChannel_16
};

#endif
#endif
#endif
