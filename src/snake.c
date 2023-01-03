#include "includes/snake.h"

Snake *snake_init(unsigned int x, unsigned int y) {
  Snake *snake = malloc(sizeof(Snake));

  snake->x = x;
  snake->y = y;
  snake->next = NULL;
  snake->prev = NULL;

  return snake;
}

int snake_valid_direction(int direction) {
  switch (direction) {
  case SNAKE_UP: {
  } break;
  case SNAKE_DOWN: {
  } break;
  case SNAKE_LEFT: {
  } break;
  case SNAKE_RIGHT: {
  } break;
  default: {
    return 0;
  } break;
  }

  return 1;
}

Snake *snake_tail(Snake **snake) {
  if (snake == NULL)
    return NULL;

  Snake *current = *snake;
  while (current->next) {
    current = current->next;
  }

  return current;
}
