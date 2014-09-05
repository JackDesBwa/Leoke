#include <Arduino.h>
#include "pads_config.h"

void cmd_keyboard_printconfig(Stream * ser, int pin) {
  if (pads[pin].flags & PADFLAG_KEYBOARD_MASK) {
    ser->print(F("keyboard "));
    ser->print(pin);
    ser->print(F(" "));
    if (pads[pin].key >= 0x20 && pads[pin].key <= 0x7e)
      ser->println(char(pads[pin].key));
    else if (KEY_LEFT_ARROW == pads[pin].key)
      ser->println(F("left"));
    else if (KEY_RIGHT_ARROW == pads[pin].key)
      ser->println(F("right"));
    else if (KEY_UP_ARROW == pads[pin].key)
      ser->println(F("up"));
    else if (KEY_DOWN_ARROW == pads[pin].key)
      ser->println(F("down"));
  }
}
  
static int str_to_key(char * key) {
  if (*key && !key[1]) {
    if (*key >= 0x20 && *key <= 0x7e)
      return *key;
    else
      return -1;
  } else if (!strcmp("left", key)) {
     return KEY_LEFT_ARROW;
  } else if (!strcmp("right", key)) {
     return KEY_RIGHT_ARROW;
  } else if (!strcmp("up", key)) {
     return KEY_UP_ARROW;
  } else if (!strcmp("down", key)) {
     return KEY_DOWN_ARROW;
  }
  return -1;
}

void cmd_keyboard(Stream * ser, int argc, char ** argv) {
  if (argc == 1) {
    int pin = str_to_pin(argv[0]);
    if (pin != -1) {
      ser->print(F("# KEYBOARD unset pad "));
      ser->print(pin);
      pads[pin].flags &= ~PADFLAG_KEYBOARD_MASK;
    } else {
      ser->print(F("# KEYBOARD wrong pad"));
    }
  } else if (argc == 2) {
    int pin = str_to_pin(argv[0]);
    if (pin != -1) {
      int key = str_to_key(argv[1]);
      if (key != -1) {
        ser->print(F("# KEYBOARD set key "));
        ser->print(argv[1]);
        ser->print(F(" to pad "));
        ser->print(pin);
        pads[pin].key = key;
        pads[pin].flags |= PADFLAG_KEYBOARD_MASK;
      }
    } else {
      ser->print(F("# KEYBOARD wrong pad"));
    }
  } else {
    ser->print(F("\
# Usage: keyboard <pad_nr> [key]\r\n\
# With one argument, it removes keyboard key of pad number pad_nr\r\n\
# With both arguments, it sets keyboard key of pad number pad_nr."));
  }
}
