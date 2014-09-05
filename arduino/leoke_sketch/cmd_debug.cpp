#include <Arduino.h>
#include "pads_config.h"

void cmd_debug(Stream * ser, int argc, char ** argv) {
  if (argc == 1) {
    if (!strcmp("on", argv[0])) {
      ser->print(F("# DEBUG active all pads"));
      for (int i = 0; i < NBPADS; ++i)
        pads[i].flags |= PADFLAG_DEBUG_MASK;
    } else if (!strcmp("off", argv[0])) {
      ser->print(F("# DEBUG disable all pads"));
      for (int i = 0; i < NBPADS; ++i)
        pads[i].flags &= ~PADFLAG_DEBUG_MASK;
    } else {
        ser->print(F("# DEBUG wrong argument"));
    }
  } else if (argc == 2) {
    int pin = str_to_pin(argv[1]);
    if (pin != -1) {
      if (!strcmp("on", argv[0])) {
        ser->print(F("# DEBUG active pad "));
        ser->print(pin);
        pads[pin].flags |= PADFLAG_DEBUG_MASK;
      } else if (!strcmp("off", argv[0])) {
        ser->print(F("# DEBUG disable pad "));
        ser->print(pin);
        pads[pin].flags &= ~PADFLAG_DEBUG_MASK;
      } else {
          ser->print(F("# DEBUG wrong argument"));
      }
    } else {
      ser->print(F("# DEBUG wrong pad"));
    }
  } else {
    ser->print(F("\
# Usage: debug <'on'|'off'> [pad_nr]\r\n\
# Print debug messages on touch."));
  }
}
