#include "includes/screen.h"

Screen *screen_init() {
  Screen *screen = calloc(1, sizeof(Screen));

  return screen;
}

void screen_setup(Screen *screen) {
  if (_in_terminal() != 1)
    Panic("Please run this program in terminal!\n");

  _load_copy_of_term_state(screen->term);

  // NOTE: &= IS keep only what is shared, so in this case, we say, keep

  screen->term.c_lflag &= ~ECHO;   // remove echo
  screen->term.c_lflag &= ~ICANON; // remove canonical mode (so we dont have to
                                   // wait for the enter key to be pressed

  _save_term_state(screen->term);
}

void screen_restore(Screen *screen) {
  // remove everything on screen
  printf("\033[2J");

  screen->term.c_lflag |= ECHO;

  _save_term_state(screen->term);
}

void screen_flush() {
  // flush screen
  fprintf(stdout, "\033[2J\033[H");
}
