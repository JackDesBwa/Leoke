#include <Arduino.h>
#include "pads_config.h"

void cmd_pullup_printconfig(Stream * ser, int pin) {
  if (pads[pin].flags & PADFLAG_PULLUP_MASK) {
    ser->print("pullup on ");
    ser->println(pin);
  }
}

void cmd_pullup(Stream * ser, int argc, char ** argv) {
  if (argc == 1) {
    // pullup on
    if (!strcmp("on", argv[0])) {
      ser->print(F("# PULLUP active all pads"));
      for (int i = 0; i < NBPADS; ++i) {
        pads[i].flags |= PADFLAG_PULLUP_MASK;
        pinMode(i, INPUT_PULLUP);
      }

    // pullup off
    } else if (!strcmp("off", argv[0])) {
      ser->print(F("# PULLUP disable all pads"));
      for (int i = 0; i < NBPADS; ++i) {
        pads[i].flags &= ~PADFLAG_PULLUP_MASK;
        pinMode(i, INPUT);
      }

    // pullup <other>
    } else {
        ser->print(F("# PULLUP wrong argument"));
    }

  } else if (argc == 2) {
    int pin = str_to_pin(argv[1]);
    if (pin != -1) {
      // pullup on <pin>
      if (!strcmp("on", argv[0])) {
        ser->print(F("# PULLUP active pad "));
        ser->print(pin);
        pads[pin].flags |= PADFLAG_PULLUP_MASK;
        pinMode(pin, INPUT_PULLUP);

      // pullup off <pin>
      } else if (!strcmp("off", argv[0])) {
        ser->print(F("# PULLUP disable pad "));
        ser->print(pin);
        pads[pin].flags &= ~PADFLAG_PULLUP_MASK;
        pinMode(pin, INPUT);

      // pullup <other> <smthg>
      } else {
          ser->print(F("# PULLUP wrong argument"));
      }

    // pullup <smthg> <wrong_number>
    } else {
      ser->print(F("# PULLUP wrong pad"));
    }

  // usage
  } else {
    ser->print(F("\
# Usage: pullup <'on'|'off'> [pad_nr]\r\n\
# Activates pullup."));
  }
}
