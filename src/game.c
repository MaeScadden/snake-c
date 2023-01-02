#include "includes/game.h"

int _game_score(Snake *snake) {
  int total = 0;
  SnakeBody *current = snake->body;

  while (current != NULL) {
    total++;
    current = current->next;
  }

  return total;
}

void _game_update(Board **board, Snake **snake) {
  //
  board_update(board, snake);
}

void _game_render(Board **board, int score) {
  screen_flush();

  Board *b = *board;

  fprintf(stdout, "Top Row\n");
  for (unsigned int row = 0; row < b->rows; ++row) {
    fprintf(stdout, "%s", b->lines[row]);
  }

  fprintf(stdout, "\n[Score: %d]\n", score);
}

int game_start_interactive(Screen **screen, Board **board, Snake **snake) {
  screen_setup(*screen);
  screen_flush();
  Snake *s = *snake;

  int quit = 0;
  while (quit == 0 && !feof(stdin)) {
    // update board
    _game_update(board, snake);
    _game_render(board, _game_score(*snake));

    int c = fgetc(stdin);
    switch (c) {
    case 'q': {
      quit = 1;
    } break;
    case 'k': {
      s->direction = SNAKE_UP;
    } break;
    case 'j': {
      s->direction = SNAKE_DOWN;
    } break;
    case 'h': {
      s->direction = SNAKE_LEFT;
    } break;
    case 'l': {
      s->direction = SNAKE_RIGHT;
    } break;
    }
    // handle control changes (lets make this a rougue like!) (after snake)
  }

  screen_restore(*screen);

  return 0;
}
