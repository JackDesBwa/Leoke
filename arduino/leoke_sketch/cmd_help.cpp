#include <Arduino.h>
#include "pads_config.h"

void cmd_help(Stream * ser, int argc, char ** argv) {
  ser->print(F("\
# HELP\r\n\
# debug    - Print debug messages on touch\r\n\
# help     - This help\r\n\
# keyboard - Set keyboard key\r\n\
"));
#ifdef MIDI_ENABLED
  ser->print(F("\
# midi     - Set midi note\r\n\
"));
#endif
  ser->print(F("\
# print    - Print current config\r\n\
# pullup   - Activate pullup\r\n\
# read     - Read GPIO state\
# reset    - Reset configuration\
"));
}
