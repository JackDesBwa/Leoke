#include <Arduino.h>
#include "shell.h"
#include "pads_config.h"

void cmd_debug(Stream * ser, int argc, char ** argv) {
  if (argc == 1) {
    if (!strcmp("on", argv[0])) {
      ser->print(F(SHELL_COMMENT " DEBUG active all pads"));
      for (int i = 0; i < NBPADS; ++i)
        pads[i].flags |= PADFLAG_DEBUG_MASK;
    } else if (!strcmp("off", argv[0])) {
      ser->print(F(SHELL_COMMENT " DEBUG disable all pads"));
      for (int i = 0; i < NBPADS; ++i)
        pads[i].flags &= ~PADFLAG_DEBUG_MASK;
    } else {
        ser->print(F(SHELL_COMMENT " DEBUG wrong argument"));
    }
  } else if (argc == 2) {
    int pin = str_to_pin(argv[1]);
    if (pin != -1) {
      if (!strcmp("on", argv[0])) {
        ser->print(F(SHELL_COMMENT " DEBUG active pad "));
        ser->print(pin);
        pads[pin].flags |= PADFLAG_DEBUG_MASK;
      } else if (!strcmp("off", argv[0])) {
        ser->print(F(SHELL_COMMENT " DEBUG disable pad "));
        ser->print(pin);
        pads[pin].flags &= ~PADFLAG_DEBUG_MASK;
      } else {
          ser->print(F(SHELL_COMMENT " DEBUG wrong argument"));
      }
    } else {
      ser->print(F(SHELL_COMMENT " DEBUG wrong pad"));
    }
  } else {
    ser->print(F("\
" SHELL_COMMENT " Usage: debug <'on'|'off'> [pad_nr]\r\n\
" SHELL_COMMENT " Print debug messages on touch."));
  }
}
