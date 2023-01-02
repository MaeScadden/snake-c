#include "includes/snake.h"

Snake *snake_init(unsigned int x, unsigned int y, int direction) {
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
    Panic("snake_init given a invalid direction[%d]\n", direction);
  } break;
  }

  SnakeBody *head = malloc(sizeof(SnakeBody));
  head->x = x;
  head->y = y;
  head->next = NULL;

  Snake *snake = malloc(sizeof(Snake));
  snake->direction = direction;
  snake->body = head;

  snake->body->prev = NULL;

  return snake;
}
void snake_move(Snake *snake);
void snake_look(Snake *snake, int direction);
