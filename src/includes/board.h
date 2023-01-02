#pragma once
#include "snake.h"
#include <stdlib.h>

#define TILE_SNAKE_HEAD_CHAR 'X'
#define TILE_SNAKE_BODY_CHAR 'x'
#define TILE_EMPTY_CHAR '~'
#define TILE_APPLE_CHAR '@'

typedef struct {
  char **lines;
  unsigned long size;
  unsigned int cols;
  unsigned int rows;
} Board;

void board_update(Board **board, Snake **snake);
Board *board_init(unsigned int width, unsigned int height);

#define CleanupBoard(_world)                                                   \
  do {                                                                         \
    if (world == NULL)                                                         \
      break;                                                                   \
    free(world->board);                                                        \
    free(world);                                                               \
  } while (0)
