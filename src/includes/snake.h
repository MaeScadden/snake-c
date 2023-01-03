#pragma once
#include <stdlib.h>

typedef struct Snake {
  unsigned int x;
  unsigned int y;
  struct Snake *next;
  struct Snake *prev;
} Snake;

typedef enum {
  SNAKE_UP,
  SNAKE_DOWN,
  SNAKE_LEFT,
  SNAKE_RIGHT,
} SnakeDirection;

Snake *snake_init(unsigned int x, unsigned int y);
int snake_valid_direction(int direction);
Snake *snake_tail(Snake **snake);
