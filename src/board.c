#include "includes/board.h"

void board_update(Board **board) {
  Board *b = *board;

  char tile = TILE_SNAKE_HEAD_CHAR;
  if (b->snake != NULL) {
    Snake *s = b->snake;

    Snake *current = &*s;
    while (current != NULL) {
      if (current->next != NULL) {
        current = current->next;
        continue;
      }

      if (current->prev != NULL) {
        current->prev->next = NULL;
        b->lines[current->y][current->x] = TILE_EMPTY_CHAR;
        free(current);
      }

      break;
    }

    Snake *new_head = malloc(sizeof(Snake));
    Snake *head = s;
    new_head->x = head->x;
    new_head->y = head->y;

    b->snake->prev = new_head;
    new_head->next = &*s;

    switch (b->snake_direction) {
    case SNAKE_LEFT: {
      if (head->x == 0) {
        Panic("Game over! snake hit left wall\n");
      }

      new_head->x = head->x - 1;
    } break;
    case SNAKE_RIGHT: {
      if (head->x == b->cols - 1) {
        Panic("Game over! snake hit right wall\n");
      }

      new_head->x = head->x + 1;
    } break;
    case SNAKE_UP: {
      if (head->y == 0) {
        Panic("Game over! snake hit top wall\n");
      }

      new_head->y = head->y - 1;
    } break;
    case SNAKE_DOWN: {
      if (head->y == b->rows - 1) {
        Panic("Game over! snake hit bottom wall\n");
      }

      new_head->y = head->y + 1;
    } break;
    }

    current = new_head->next;
    while (current != NULL) {
      unsigned int current_x = current->x;
      unsigned int head_x = new_head->x;
      if (new_head->x == current->x) {
        if (new_head->y == current->y) {
          Panic("Game over! snake hit self {x: %d, y: %d}\n", head_x,
                current_x);
        }
      }

      current = current->next;
    }

    b->snake = new_head;

    current = &*b->snake;
    while (current != NULL) {
      b->lines[current->y][current->x] = tile;
      current = current->next;
      tile = TILE_SNAKE_BODY_CHAR;
    }
  }

  /*
  Fruit *fruit = b->fruit;
  while (fruit) {
    Snake snake_body = &*b->snake;
  }
  */
}

Board *board_init(unsigned int cols, unsigned int rows,
                  int snake_start_direction) {
  Board *board = malloc(sizeof(Board));
  board->rows = rows;
  board->cols = cols;

  if (!snake_valid_direction(snake_start_direction))
    Panic("snake direction of value[%d] is not valid\n", snake_start_direction);

  board->snake_direction = snake_start_direction;
  board->snake = snake_init(20, 8);

  board->lines = malloc(sizeof(char *) * board->rows);

  for (unsigned int row = 0; row < rows; ++row) {
    board->lines[row] = malloc(sizeof(char) * board->cols + 1);

    for (unsigned int col = 0; col < board->cols; ++col) {
      board->lines[row][col] = TILE_EMPTY_CHAR;
    }

    board->lines[row][cols] = '\n';
  }

  board_update(&board);

  return board;
}
