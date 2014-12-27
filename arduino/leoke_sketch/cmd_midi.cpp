#include <Arduino.h>
#include "shell.h"
#include "pads_config.h"

#ifdef MIDI_ENABLED

void cmd_midi_printconfig(Stream * ser, int pin) {
  if (pads[pin].flags & PADFLAG_MIDI_MASK) {
    const char * notestr[] = {
      "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"
    };
    ser->print(F("midi "));
    ser->print(pin);
    ser->print(F(" "));
    ser->print(notestr[pads[pin].note]);
    ser->print((pads[pin].octave / 12) - 1);
    ser->print(F(" "));
    ser->print(pads[pin].channel + 1);
    ser->print(F(" "));
    ser->println(pads[pin].velocity);
  }
}

bool str_to_note(char * str, enum MidiNote * note) {
  int noteres;

  if (*str && *str >= 'A' && *str <= 'G') {
    noteres = *str - 'C';
    if (noteres < 0) noteres = noteres + 7;
    noteres *= 2;
    if (noteres > 4) noteres -= 1;
    ++str;
  } else {
    return 0;
  }

  if (*str && (*str == '#')) {
    noteres += 1;
    ++str;
    if (noteres == 5) return 0;
    if (noteres == 12) return 0;

  } else if (*str && (*str == 'b')) {
    noteres -= 1;
    ++str;
    if (noteres == -1) return 0;
    if (noteres == 4) return 0;
  }

  if (*str && *str >= '0' && *str <= '9' && *(str+1) == 0) {
    *note = MidiNote(noteres);
    return 1;
  }

  return 0;
}

bool str_to_octave(char * str, enum MidiOctave * octave) {
  if (*str && *str >= 'A' && *str <= 'G')
    ++str;
  else
    return 0;

  if (*str && (*str == '#' || *str == 'b'))
    ++str;

  if (*str && *str >= '0' && *str <= '9' && *(str+1) == 0) {
    *octave = MidiOctave((*str - '0' + 1) * 12);
    return 1;
  }

  return 0;
}

void cmd_midi(Stream * ser, int argc, char ** argv) {
  if (argc > 0 && argc < 5) {
    int pin = str_to_pin(argv[0]);
    if (pin != -1) {
      // midi <pin>
      if (argc == 1) {
        ser->print(F(SHELL_COMMENT " MIDI remove config of pad "));
        ser->print(pin);
        pads[pin].flags &= ~PADFLAG_MIDI_MASK;

      // midi <pin> ......
      } else {
        enum MidiNote note = MidiNote_C;
        enum MidiOctave octave = MidiOctave_3;
        enum MidiChannel channel = MidiChannel_1;
        int velocity = 64;

        if (!str_to_note(argv[1], &note)) {
          ser->print(F(SHELL_COMMENT " MIDI wrong note"));
          return;
        }

        if (!str_to_octave(argv[1], &octave)) {
          ser->print(F(SHELL_COMMENT " MIDI wrong octave"));
          return;
        }

        if (argc > 2) {
          int tmpchannel = atoi(argv[2]);
          if (tmpchannel < 1 || tmpchannel > 16) {
            ser->print(F(SHELL_COMMENT " MIDI wrong channel"));
            return;
          }
          channel = MidiChannel(tmpchannel - 1);
        }

        if (argc == 4) {
          int tmpvelocity = atoi(argv[3]);
          if (tmpvelocity < 0 || tmpvelocity > 127) {
            ser->print(F(SHELL_COMMENT " MIDI wrong veocity"));
            return;
          }
          velocity = tmpvelocity;
        }

        ser->print(F(SHELL_COMMENT " MIDI assign "));
        ser->print(argv[1]);
        ser->print(" to pad ");
        ser->print(pin);
        ser->print(F(" with channel "));
        ser->print(int(channel) + 1);
        ser->print(F(" and velocity "));
        ser->print(velocity);

        pads[pin].note = note;
        pads[pin].octave = octave;
        pads[pin].channel = channel;
        pads[pin].velocity = velocity;
        pads[pin].flags |= PADFLAG_MIDI_MASK;
      }
    } else {
      ser->print(F(SHELL_COMMENT " MIDI wrong pad"));
    }
  } else {
    ser->print(F("\
" SHELL_COMMENT " Usage: midi <pad_nr> [note_octave] [channel] [velocity]\r\n\
" SHELL_COMMENT " With one argument, it removes midi config of pad number pad_nr.\r\n\
" SHELL_COMMENT " With note_octave argument, it assigns this note to pad number pad_nr. It of the form C7.\r\n\
" SHELL_COMMENT " With channel argument, it assigns this note to pad number pad_nr on specified channel.\r\n\
" SHELL_COMMENT " With all arguments, it assigns this note to pad number pad_nr with a custom velocity."));
  }
}

#endif
