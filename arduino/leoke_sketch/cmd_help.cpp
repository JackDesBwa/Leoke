#include <Arduino.h>
#include "shell.h"
#include "pads_config.h"

void cmd_help(Stream * ser, int argc, char ** argv) {
  ser->print(F("\
" SHELL_COMMENT " HELP\r\n\
" SHELL_COMMENT " debug    - Print debug messages on touch\r\n\
" SHELL_COMMENT " eeprom   - Save/resore configuration in EEPROM\r\n\
" SHELL_COMMENT " help     - This help\r\n\
" SHELL_COMMENT " keyboard - Set keyboard key\r\n\
"));
#ifdef MIDI_ENABLED
  ser->print(F("\
" SHELL_COMMENT " midi     - Set midi note\r\n\
"));
#endif
  ser->print(F("\
" SHELL_COMMENT " print    - Print current config\r\n\
" SHELL_COMMENT " pullup   - Activate pullup\r\n\
" SHELL_COMMENT " read     - Read GPIO state\r\n\
" SHELL_COMMENT " reset    - Reset configuration\
"));
}
