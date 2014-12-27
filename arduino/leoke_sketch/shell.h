#ifndef SHELL_H
#define SHELL_H

#include <Arduino.h>

#define SHELL_COMMENT ":"

struct ShellConf {
  char * cmd;
  void (*fct)(Stream * ser, int argc, char ** argv);
};

void shell_init(Stream & serial, const ShellConf * confs, int size, const char * const motd);

void shell_loop();

#endif
