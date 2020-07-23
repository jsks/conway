#include <err.h>
#include <stdbool.h>
#include <string.h>

#include "matrix.h"

Board *new_board(size_t rows, size_t columns) {
  Board *board = malloc(sizeof(Board));

  board->rows = rows;
  board->columns = columns;
  if (!(board->data = malloc(rows * sizeof(int *))))
      err(EXIT_FAILURE, NULL);

  for (size_t i = 0; i < rows; i++) {
    if (!(board->data[i] = calloc(columns, sizeof(int))))
        err(EXIT_FAILURE, NULL);
  }

  return board;
}

void random_populate(Board *board, double probability) {
  for (size_t i = 0; i < board->rows; i++) {
    for (size_t j = 0; j < board->columns; j++) {
      // TODO: this is a terrible way to simulate Bernoulli(1)
      board->data[i][j] = rand() % 10 < (probability * 10);
    }
  }
}

Board *copy(Board *board) {
  Board *new = new_board(board->rows, board->columns);
  for (size_t i = 0; i < board->rows; i++) {
    memcpy(new->data[i], board->data[i], board->columns * sizeof(int));
  }

  return new;
}

void destroy(Board *p) {
  for (size_t i = 0; i < p->rows; i++) {
    free(p->data[i]);
  }

  free(p->data);
  free(p);
}

int get(Board *board, Coordinates p) {
  if (p.x >= board->rows || p.y >= board->columns)
    return -1;

  return board->data[p.x][p.y];
}

void toggle(Board *board, Coordinates p) {
  if (p.x >= board->rows || p.y >= board->columns)
    return;

  board->data[p.x][p.y] = (board->data[p.x][p.y] == 1) ? 0 : 1;
}

unsigned int neighbourhood_sum(Board *board, Coordinates p) {
  unsigned int sum = 0;

  int start_row = p.x - 1, end_row = p.x + 2,
    start_col = p.y - 1, end_col = p.y + 2;

  for (int i = start_row; i < end_row; i++) {
    for (int j = start_col; j < end_col; j++) {
      sum += board->data[i % board->rows][j % board->columns];
    }
  }

  return sum;
}

bool is_empty(Board *board) {
  for (size_t i = 0; i < board->rows; i++) {
    for (size_t j = 0; j < board->columns; j++) {
      if (board->data[i][j] == 1)
        return false;
    }
  }

  return true;
}
