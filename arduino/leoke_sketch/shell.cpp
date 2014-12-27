#include "shell.h"

// Stream to compute
static Stream * ser;

// Shell configs
static const ShellConf * shellconfs;
static int shellconf_size;

// Input buffer
#define INPUT_BUFFER_SIZE 120
static char input_buffer[INPUT_BUFFER_SIZE];
static char * input_insert;
static unsigned char input_comment;

// Arguments buffer
#define MAX_ARGS 10
static char * arguments[MAX_ARGS];

// Prompt
static const char * const prompt = "$ ";

static unsigned char is_ignored_start_char(unsigned char chr) {
  return chr == ' ' || chr == '$';
}

static char * next_arg(char * args) {
  char * res = args;
  while (*res != ' ' && *res != 0) ++res;
  if (*res == 0) return 0;
  *res = 0;
  ++res;
  while (*res == ' ') ++res;
  if (*res == 0) return 0;
  return res;
}

void shell_init(Stream & serial, const ShellConf * confs, int size, const char * const motd) {
  ser = &serial;
  shellconfs = confs;
  shellconf_size = shellconfs ? size : 0;
  input_insert = input_buffer;
  input_comment = 0;
  ser->write(motd);
  ser->write("\r\n");
  ser->write(prompt);
}

void shell_loop() {
  if (ser->available()) {
    // Input data except for comments
    int chr_real = ser->read();
    int  chr = (chr_real < 0x20 || chr_real > 0x7e) ? 0 : chr_real;
    if (!input_comment && chr) {
      *input_insert = chr;
      ++input_insert;
    }
    if (input_insert == input_buffer + INPUT_BUFFER_SIZE) input_insert = input_buffer + INPUT_BUFFER_SIZE - 1;
    const char * comment = SHELL_COMMENT;
    if (chr == comment[0]) input_comment = 1;

    // Handle CTRL-C
    if (chr_real == 3) {
      ser->write("\r" SHELL_COMMENT "\r\n");
      ser->write(prompt);
      input_insert = input_buffer;
      input_comment = 0;

    // Command validated
    } else if (chr_real == '\r' || chr_real == '\n') {
      // Clear our command
      char * mycmd_orig = input_buffer;
      *input_insert = 0;
      while (is_ignored_start_char(*mycmd_orig) && mycmd_orig < input_insert) ++mycmd_orig;

      // Find shellconf
      const ShellConf * cfg = shellconfs;
      char * mycmd;
      int i;
      for (i = 0; i < shellconf_size; ++i) {
        char * cmd = cfg->cmd;
        mycmd = mycmd_orig;
        while (is_ignored_start_char(*cmd) && *cmd) ++cmd;
        while (*mycmd == *cmd && *cmd) ++cmd, ++mycmd;
        if (*cmd == 0 && (*mycmd == ' ' || *mycmd == 0)) break;
        ++cfg;
      }

      // Command is valid, execute
      if (i < shellconf_size) {
        ser->write("\r\n");
        while (*mycmd == ' ' && *mycmd) ++mycmd;
        int nb_arguments = 0;
        char * arg = mycmd;
        while (arg && nb_arguments < MAX_ARGS) {
          arguments[nb_arguments] = arg;
          if (*arg == 0) --nb_arguments;
          arg = next_arg(arg);
          ++nb_arguments;
        }
        cfg->fct(ser, nb_arguments, arguments);
      } else if (*mycmd) {
        ser->write("\r\n" SHELL_COMMENT " Wrong command, see help");
      }

      // Display prompt again
      ser->write("\r\n");
      ser->write(prompt);
      input_insert = input_buffer;
      input_comment = 0;

    // Otherwise, just echo what is accepted
    } else if (chr != 0) {
      ser->write(chr);
    }
  }
}

