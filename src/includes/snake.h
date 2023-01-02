#pragma once
#include "print.h"
#include <stdlib.h>

typedef struct SnakeBody {
  unsigned int x;
  unsigned int y;
  struct SnakeBody *next;
  struct SnakeBody *prev;
} SnakeBody;

typedef struct {
  SnakeBody *body;
  enum {
    SNAKE_UP,
    SNAKE_DOWN,
    SNAKE_LEFT,
    SNAKE_RIGHT,
  } direction;
} Snake;

Snake *snake_init(unsigned int x, unsigned int y, int direction);
void snake_move(Snake *snake);
void snake_look(Snake *snake, int direction);
