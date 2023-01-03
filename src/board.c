#include "includes/board.h"

void _board_eat_fruit(Board **board, Fruit **target) {
  if (target == NULL)
    Panic("Cannot eat fruit it is null, logical error calling "
          "_board_eat_fruit\n");

  Board *b = *board;
  Fruit *to_eat = *target;
  int is_start_fruit = b->fruit == to_eat;

  Fruit *previous = to_eat->prev;
  Fruit *next = to_eat->next;
  free(to_eat);

  if (previous != NULL) {
    if (is_start_fruit)
      Panic("Start fruit should not have a non NULL prev value\n");

    if (next != NULL) {
      previous->next = next;
      next->prev = previous;
      return;
    }

    previous->next = NULL;
    return;
  }

  if (!is_start_fruit)
    Panic("Fruit eaten does not have a prev value and is not the board->fruit, "
          "assignment has gone wrong\n");

  if (next != NULL) {
    b->fruit = next;
    return;
  }

  b->fruit = NULL;
}

void board_free_space(unsigned int *x, unsigned int *y, Board **board) {
  Board *b = *board;

  while (1) {
    *x = rand_num(0, b->cols - 2);
    *y = rand_num(0, b->rows - 1);

    char tile = b->lines[*y][*x];
    if (tile == TILE_EMPTY_CHAR) {
      break;
    }
  }
}

Fruit *_board_new_fruit(Board **board) {
  unsigned int x = 0;
  unsigned int y = 0;

  board_free_space(&x, &y, board);

  return fruit_init(x, y);
}

void _board_add_fruit(Board **board) {
  Board *b = *board;
  Fruit *to_add = _board_new_fruit(board);

  if (b->fruit == NULL) {
    b->fruit = to_add;
  } else {
    fruit_push(&b->fruit, &to_add);
  }

  b->lines[to_add->y][to_add->x] = TILE_FRUIT_CHAR;
}

void board_update(Board **board) {
  Board *b = *board;

  char tile = TILE_SNAKE_HEAD_CHAR;
  if (b->snake != NULL) {
    Snake *s = b->snake;

    Snake *new_head = malloc(sizeof(Snake));
    Snake *head = s;
    new_head->x = head->x;
    new_head->y = head->y;

    b->snake->prev = new_head;
    new_head->next = head;

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

    Snake *current = new_head->next;
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
    Info("After\n");
  }

  Fruit *fruit = b->fruit;

  int ate = 0;
  while (fruit != NULL) {
    if (fruit->x == b->snake->x) {
      if (fruit->y == b->snake->y) {
        ate = 1;
        break;
      }
    }

    fruit = fruit->next;
  }

  if (ate) {
    _board_eat_fruit(board, &fruit);
    _board_add_fruit(board);
  } else {
    if (b->snake != NULL && b->snake->next != NULL) {
      Snake *last = snake_tail(&b->snake);
      last->prev->next = NULL;

      b->lines[last->y][last->x] = TILE_EMPTY_CHAR;
      free(last);
    }
  }
}

void _board_lines_init(Board **board) {
  Board *b = *board;

  b->lines = malloc(sizeof(char *) * b->rows);

  for (unsigned int row = 0; row < b->rows; ++row) {
    b->lines[row] = malloc(sizeof(char) * b->cols + 1);

    for (unsigned int col = 0; col < b->cols; ++col) {
      b->lines[row][col] = TILE_EMPTY_CHAR;
    }

    b->lines[row][b->cols] = '\n';
  }

  board_update(board);
}

Board *board_init(unsigned int cols, unsigned int rows,
                  int snake_start_direction) {
  if (!snake_valid_direction(snake_start_direction))
    Panic("snake direction of value[%d] is not valid\n", snake_start_direction);

  Board *board = malloc(sizeof(Board));
  board->snake_direction = snake_start_direction;
  board->rows = rows;
  board->cols = cols;
  board->snake = snake_init(cols / 2, rows / 2);
  _board_lines_init(&board);
  _board_add_fruit(&board);

  return board;
}
