#include "includes/game.h"

int _game_score(Snake **snake) {
  int total = 0;
  Snake *current = *snake;

  while (current != NULL) {
    total++;
    current = current->next;
  }

  return total;
}

void _game_update(Board **board) {
  //
  board_update(board);
}

void _game_render(Board **board, int score) {

  screen_flush();

  Board *b = *board;

  fprintf(stdout, "Snake in c         [Fruits]: %d\n", score);

  fprintf(stdout, "╔═");
  for (unsigned int col = 1; col < b->cols; ++col) {
    fprintf(stdout, "══");
  }
  fprintf(stdout, "══╗\n");

  for (unsigned int row = 0; row < b->rows; ++row) {
    fprintf(stdout, "║");
    for (unsigned int col = 0; col < b->cols; ++col) {
      fprintf(stdout, " %c", b->lines[row][col]);
    }
    fprintf(stdout, " ║\n");
  }

  fprintf(stdout, "╚═");
  for (unsigned int col = 1; col < b->cols; ++col) {
    fprintf(stdout, "══");
  }
  fprintf(stdout, "══╝\n");
}

int game_start_interactive(Screen **screen, Board **board) {
  screen_setup(*screen);
  screen_flush();

  Board *b = (*board);

  int quit = 0;
  while (quit == 0 && !feof(stdin)) {
    _game_update(board);
    _game_render(board, _game_score(&b->snake));

    int c = fgetc(stdin);
    switch (c) {
    case 'q': {
      quit = 1;
    } break;
    case 'k': {
      b->snake_direction = SNAKE_UP;
    } break;
    case 'j': {
      b->snake_direction = SNAKE_DOWN;
    } break;
    case 'h': {
      b->snake_direction = SNAKE_LEFT;
    } break;
    case 'l': {
      b->snake_direction = SNAKE_RIGHT;
    } break;
    }
  }

  screen_restore(*screen);

  return 0;
}
