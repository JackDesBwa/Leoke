#ifndef CMDS_H
#define CMDS_H

void cmd_debug(Stream * ser, int argc, char ** argv);

void cmd_help(Stream * ser, int argc, char ** argv);

void cmd_keyboard(Stream * ser, int argc, char ** argv);
void cmd_keyboard_printconfig(Stream * ser, int pin);

#ifdef MIDI_ENABLED
void cmd_midi(Stream * ser, int argc, char ** argv);
void cmd_midi_printconfig(Stream * ser, int pin);
#endif

void cmd_print(Stream * ser, int argc, char ** argv);

void cmd_pullup(Stream * ser, int argc, char ** argv);
void cmd_pullup_printconfig(Stream * ser, int pin);

void cmd_read(Stream * ser, int argc, char ** argv);

void cmd_reset(Stream * ser, int argc, char ** argv);

#endif
