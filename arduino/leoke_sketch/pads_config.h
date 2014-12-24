#ifndef PADS_CONFIG_H
#define PADS_CONFIG_H

extern const int NBPADS;

// Pad configuration and data structure
struct Pad {
#ifdef MIDI_ENABLED
  // Midi conf
  enum MidiNote note;
  enum MidiOctave octave;
  enum MidiChannel channel;
  unsigned char velocity;
#endif

  // Keyboard conf
  unsigned char key;

  // Mouse conf
  unsigned char btn;

  // Data & conf flags
  unsigned char flags;
};


#define PADFLAG_ON_MASK 0x01
#define PADFLAG_MIDI_MASK 0x02
#define PADFLAG_KEYBOARD_MASK 0x04
#define PADFLAG_MOUSE_MASK 0x08
#define PADFLAG_DEBUG_MASK 0x10
#define PADFLAG_PULLUP_MASK 0x20

#define NBPADS 32 // Very ugly, but Arduino pseudo-abstraction do not allow to do it nicely
                  // ...and you do not want to know that there is no boundary check in official Arduino API
extern Pad pads[NBPADS];

static inline int str_to_pin(char * str) {
  if (*str == 0) return -1;
#ifdef LEOKE
  bool leoke = false;
  if (*str == 'L') {
    leoke = true;
    ++str;
  }
#endif
  int res = 0;
  while(*str) {
    res *= 10;
    if (*str >= 0x30 && *str <= 0x39)
      res += *str - 0x30;
    else return -1;
    ++str;
  }
  if (res > NBPADS) return -1;
#ifdef LEOKE
  if (leoke) {
    if (res >= sizeof(L)/sizeof(*L))
      return -1;
    else
      return L[res];
  }
#endif
  return res;
}

#endif
