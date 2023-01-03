#pragma once
#include "print.h"
#include <stdlib.h>

typedef struct Fruit {
  unsigned int x;
  unsigned int y;
  struct Fruit *next;
  struct Fruit *prev;
} Fruit;

Fruit *fruit_init(unsigned int x, unsigned int y);
void fruit_push(Fruit **fruit, Fruit **to_add);
