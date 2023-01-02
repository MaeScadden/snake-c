#pragma once
#include "print.h"
#include "termios.h"
#include <stdio.h>
#include <unistd.h>

typedef struct {
  struct termios term;
} Screen;

Screen *screen_init();
void screen_setup(Screen *screen);
void screen_restore(Screen *screen);
void screen_flush();

#define _in_terminal() isatty(0)
#define _store_snapshot_of_terminal(termios_terminal)                          \
  tcgetattr(0, termios_terminal)

#define _update_terminal(termios_terminal) tcsetattr(0, 0, termios_terminal)

#define _load_copy_of_term_state(termios_terminal)                             \
  do {                                                                         \
    int code = _store_snapshot_of_terminal(&termios_terminal);                 \
                                                                               \
    if (code < 0) {                                                            \
      Panic("Could not store the state of the terminal: code %d\n", code);     \
    }                                                                          \
  } while (0)

#define _save_term_state(termios_terminal)                                     \
  do {                                                                         \
    int code = _update_terminal(&termios_terminal);                            \
                                                                               \
    if (code) {                                                                \
      Panic("Could not update the state of the terminal: code %d\n", code);    \
    }                                                                          \
  } while (0)
