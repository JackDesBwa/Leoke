/*
The MIT License (MIT)
Copyright (c) 2014 JackDesBwa

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include <EEPROM.h> // Needed because of Arduino scrap

#include "shell.h"
#include "pads_config.h"
#include "cmds.h"

/******************************
** Data for touch and events **
******************************/

Pad pads[NBPADS];
long time;

/*******************
** Shell commands **
*******************/

const PROGMEM char * const motd = "\r\n\
# ***************************\r\n\
#  _                _\r\n\
# | |     ____     | |   ____\r\n\
# | |     ___  ___ | | _____\r\n\
# | |    / _ \\/ _ \\| |/ / _ \\\r\n\
# | |___|  __/ (_) |   <  __/\r\n\
# \\_____/\\___|\\___/|_|\\_\\___|\r\n\
#  http://leoke.desbwa.org/\r\n\
# ***************************\r\n\
#      Try help for help\r\n\
# ***************************\r\n";

const ShellConf shellconfig[] = {
  {"debug", cmd_debug},
  {"eeprom", cmd_eeprom},
  {"help", cmd_help},
  {"keyboard", cmd_keyboard},
#ifdef MIDI_ENABLED
  {"midi", cmd_midi},
#endif
  {"print", cmd_print},
  {"pullup", cmd_pullup},
  {"read", cmd_read},
  {"reset", cmd_reset},
};

/********************
** Usual functions **
********************/

// Init function
void setup() {
  Serial.begin(115200);
  Keyboard.begin();
  Mouse.begin();
  while(!Serial);
  time = millis();
  char * arg = "load";
  cmd_eeprom(&Serial, 1, &arg);
  shell_init(Serial, shellconfig, sizeof(shellconfig)/sizeof(*shellconfig), motd);
}

// Loop function
void loop() {
  if (time < millis()) {
    for (int i = 0; i < NBPADS; ++i) {
      if ((digitalRead(i) ^ pads[i].flags) & PADFLAG_ON_MASK) {
        if (pads[i].flags & PADFLAG_DEBUG_MASK) {
          Serial.print("# PAD ");
          Serial.print(i);
          Serial.print(" = ");
          Serial.println(pads[i].flags & PADFLAG_ON_MASK);
        }
        if (pads[i].flags & PADFLAG_KEYBOARD_MASK) {
          if (pads[i].flags & PADFLAG_ON_MASK)
            Keyboard.press(pads[i].key);
          else
            Keyboard.release(pads[i].key);
        }
#ifdef MIDI_ENABLED
        if (pads[i].flags & PADFLAG_MIDI_MASK) {
          MIDIUSB.note(pads[i].flags & PADFLAG_ON_MASK, pads[i].note, pads[i].octave, pads[i].channel, pads[i].velocity);
        }
#endif
        pads[i].flags ^= 1;
      }
    }
#ifdef MIDI_ENABLED
    MIDIUSB.flush();
#endif
    time = millis() + 100;
  }

  shell_loop();
}

