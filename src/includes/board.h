#pragma once
#include "fruit.h"
#include "print.h"
#include "snake.h"
#include <stdlib.h>

#define TILE_SNAKE_HEAD_CHAR 'X'
#define TILE_SNAKE_BODY_CHAR 'x'
#define TILE_EMPTY_CHAR '~'
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
Board *board_init(unsigned int width, unsigned int height,
                  int snake_start_direction);
void board_free_space(unsigned int *x, unsigned int *y, Board **board);

#define rand_num(min, max) (rand() % (max - min + 1)) + min

#define CleanupBoard(_world)                                                   \
  do {                                                                         \
    if (world == NULL)                                                         \
      break;                                                                   \
    free(world->board);                                                        \
    free(world->snake);                                                        \
    free(world);                                                               \
  } while (0)
