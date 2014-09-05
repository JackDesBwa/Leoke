#include <Arduino.h>
#include "pads_config.h"

void cmd_read(Stream * ser, int argc, char ** argv) {
  if (argc == 1) {
    int pin = str_to_pin(argv[0]);
    if (pin != -1) {
      ser->print(F("# READ pad "));
      ser->print(pin);
      ser->print(F(" = "));
      ser->print(pads[pin].flags & PADFLAG_ON_MASK);
    } else {
      ser->print(F("# READ wrong pad"));
    }
  } else {
    ser->print(F("\
# Usage: read <pad_nr>\r\n\
# Reads current status of pad number pad_nr."));
  }
}
