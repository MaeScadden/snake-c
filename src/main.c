#include "includes/board.h"
#include "includes/game.h"
#include "includes/print.h"
#include "includes/screen.h"
#include <unistd.h>

int usage() {
  printf("Usage: ./main <width: int > 5> <height: int > 5>\n");
  return 1;
}

int main(int argc, char **argv) {
  if (argc != 3)
    return usage();

  int width = atoi(argv[1]);
  int height = atoi(argv[2]);

  if (width < 5 || height < 5)
    return usage();

  Board *board = board_init(width, height, 0);
  Screen *screen = screen_init();

  return game_start_interactive(&screen, &board);
}
