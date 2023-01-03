#include "includes/board.h"
#include "includes/game.h"
#include "includes/print.h"
#include "includes/screen.h"
#include <unistd.h>

int main(int argc, char **argv) {
  int width = 8;
  int height = 10;

  if (argc == 2) {
    width = atoi(argv[1]);
  } else if (argc == 3) {
    width = atoi(argv[1]);
    height = atoi(argv[2]);
  }

  Board *board = board_init(width, height, 0);
  Screen *screen = screen_init();

  return game_start_interactive(&screen, &board);
}
