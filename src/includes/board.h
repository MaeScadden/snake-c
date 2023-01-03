#pragma once
#include "fruit.h"
#include "print.h"
#include "rand.h"
#include "snake.h"
#include <stdlib.h>

#define TILE_SNAKE_HEAD_CHAR '/'
#define TILE_SNAKE_BODY_CHAR '|'
#define TILE_EMPTY_CHAR ' '
#define TILE_FRUIT_CHAR '@'

typedef struct {
  char **lines;
  unsigned long size;
  unsigned int cols;
  unsigned int rows;
  Snake *snake;
  SnakeDirection snake_direction;
  Fruit *fruit;
} Board;

void board_update(Board **board);
void board_free_space(unsigned int *x, unsigned int *y, Board **board);
Board *board_init(unsigned int width, unsigned int height,
                  int snake_start_direction);
