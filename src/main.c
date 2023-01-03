#include "includes/board.h"
#include "includes/game.h"
#include "includes/print.h"
#include "includes/screen.h"

int main(void) {
  Board *board = board_init(8, 15, 0);
  Screen *screen = screen_init();

  return game_start_interactive(&screen, &board);
}
