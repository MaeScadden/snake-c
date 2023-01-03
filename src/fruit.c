#include "includes/fruit.h"

Fruit *fruit_init(unsigned int x, unsigned int y) {
  Fruit *fruit = malloc(sizeof(Fruit));

  fruit->x = x;
  fruit->y = y;
  fruit->next = NULL;
  fruit->prev = NULL;

  return fruit;
}

void fruit_push(Fruit **fruit, Fruit **to_add) {
  if (fruit == NULL)
    Panic("fruit_push: cannot push onto NULL fruit\n");

  if (to_add == NULL)
    Panic("fruit_push: cannot push onto fruit with NULL value\n");

  Fruit *current = *fruit;
  while (1) {
    if (current->next == NULL)
      break;

    current = current->next;
  }

  current->next = *to_add;
  (*to_add)->prev = &*current;
}
