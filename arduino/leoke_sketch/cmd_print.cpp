#include <Arduino.h>
#include "cmds.h"
#include "pads_config.h"

static void print_conf(Stream * ser, int nr) {
  cmd_keyboard_printconfig(ser, nr);
#ifdef MIDI_ENABLED
  cmd_midi_printconfig(ser, nr);
#endif
  cmd_pullup_printconfig(ser, nr);
}

void cmd_print(Stream * ser, int argc, char ** argv) {
  if (argc == 1) {
    if (!strcmp("all", argv[0])) {
      ser->print(F("# PRINT config of all pads\r\nreset\r\n"));
      for (int i = 0; i < NBPADS; ++i)
        print_conf(ser, i);
    } else {
      int pin = str_to_pin(argv[0]);
      if (pin != -1) {
        ser->print(F("# PRINT config of pad "));
        ser->println(pin);
        print_conf(ser, pin);
      } else {
        ser->print(F("# PRINT wrong pad"));
      }
    }
  } else {
    ser->print(F("# Usage: print <pad_nr|'all'>\r\n\
# Print configuration related to pad number pad_nr, or all pads."));
  }
}
