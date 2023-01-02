#include "includes/board.h"
#include "includes/game.h"
#include "includes/print.h"
#include "includes/screen.h"

int main(void) {
  Board *board = board_init(30, 15);
  Screen *screen = screen_init();
  Snake *snake = snake_init(20, 8, 0);

  return game_start_interactive(&screen, &board, &snake);
}
