#ifndef _board_h
#define _board_h

#include <stdbool.h>
#include <stdlib.h>

#define Cpair(x, y) (Coordinates) { x, y }

typedef struct {
  size_t rows, columns;
  int **data;
} Board;

typedef struct {
  size_t x, y;
} Coordinates;

Board *init_board(size_t, size_t);
void set(Board *, Coordinates);
void unset(Board *, Coordinates);
bool isset(Board *, Coordinates);
void center(Board **);
void copy(Board *, Board **);
void destroy(Board *);

unsigned int neighbourhood_sum(Board *, Coordinates);
void rpopulate(Board *, double);

#endif
