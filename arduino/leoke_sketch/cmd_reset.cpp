#include <Arduino.h>
#include "shell.h"
#include "pads_config.h"

void cmd_reset(Stream * ser, int argc, char ** argv) {
  if (argc == 0 || (argc == 1 && !strcmp("quiet", argv[0]))) {
    if (argc == 0)
      ser->print(F(SHELL_COMMENT " RESET"));

    for (int i = 0; i < NBPADS; ++i) {
#ifdef MIDI_ENABLED
      pads[i].note = MidiNote_C;
      pads[i].octave = MidiOctave_3;
      pads[i].channel = MidiChannel_1;
      pads[i].velocity = 64;
#endif
      pads[i].key = ' ';
      pads[i].btn = 0;
      pads[i].flags = 0;

      digitalWrite(i, LOW);
      pinMode(i, INPUT);
    }
  } else {
    ser->print(F("\
" SHELL_COMMENT " Usage: reset ['quiet']\r\n\
" SHELL_COMMENT " Reset configuration."));
  }
}
