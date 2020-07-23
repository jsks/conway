#ifndef _matrix_h
#define _matrix_h

#include <stdbool.h>
#include <stdlib.h>

typedef struct {
  size_t rows;
  size_t columns;
  int **data;
} Board;

typedef struct {
  size_t x;
  size_t y;
} Coordinates;

Board *new_board(size_t, size_t);
void random_populate(Board *, double);
Board *copy(Board *);
void destroy(Board *);
int get(Board *, Coordinates);
void toggle(Board *, Coordinates);
unsigned int neighbourhood_sum(Board *, Coordinates);
bool is_empty(Board *);

#endif
