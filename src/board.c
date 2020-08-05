#include <err.h>
#include <stdbool.h>
#include <string.h>

#include "board.h"

Board *init_board(size_t rows, size_t columns) {
  Board *board;

  if (!(board = malloc(sizeof(Board))))
    err(EXIT_FAILURE, NULL);

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

Coordinates find_min_cell(Board *board) {
  for (size_t i = 0; i < board->rows; i++) {
    for (size_t j = 0; j < board->columns; j++) {
      if (isset(board, (Coordinates){ i, j }))
        return (Coordinates){ i, j };
    }
  }

  return (Coordinates){ 0, 0 };
}

Coordinates find_max_cell(Board *board) {
  for (size_t i = board->rows - 1; i > 0; i--) {
    for (size_t j = board->columns - 1; j > 0; j--) {
      if (isset(board, (Coordinates){ i, j }))
        return (Coordinates){ i, j };
    }
  }

  return (Coordinates){ 0, 0 };
}

void center(Board **board) {
  Board *new = init_board((*board)->rows, (*board)->columns);

  Coordinates min = find_min_cell(*board), max = find_max_cell(*board);

  size_t offset_x = ((*board)->rows - max.x - 1) / 2 - min.x,
         offset_y = ((*board)->columns - max.y - 1) / 2 - min.y;

  for (size_t i = min.x; i <= max.x; i++) {
    for (size_t j = 0; j < (*board)->columns; j++) {
      if (isset(*board, (Coordinates){ i, j }))
        set(new, (Coordinates){ i + offset_x, j + offset_y });
    }
  }

  destroy(*board);
  *board = new;
}

void set(Board *board, Coordinates pos) {
  board->data[pos.x][pos.y] = 1;
}

void unset(Board *board, Coordinates pos) {
  board->data[pos.x][pos.y] = 0;
}

bool isset(Board *board, Coordinates pos) {
  return board->data[pos.x][pos.y] > 0;
}

unsigned int neighbourhood_sum(Board *board, Coordinates p) {
  unsigned int sum = 0;

  int start_row = (p.x == 0) ? 0 : p.x - 1, end_row = (p.x == board->rows - 1) ? p.x + 1 : p.x + 2,
      start_col = (p.y == 0) ? 0 : p.y - 1,
      end_col = (p.y == board->columns - 1) ? p.y + 1 : p.y + 2;

  for (int i = start_row; i < end_row; i++) {
    for (int j = start_col; j < end_col; j++) {
      sum += isset(board, (Coordinates){ i, j });
    }
  }

  return sum;
}

/* TODO: this is a terrible way to simulate Bernoulli(1) */
void rpopulate(Board *board, double probability) {
  for (size_t i = 0; i < board->rows; i++) {
    for (size_t j = 0; j < board->columns; j++) {
      board->data[i][j] = rand() % 10 < (probability * 10);
    }
  }
}

void copy(Board *src, Board **dest) {
  if (!(*dest))
    *dest = init_board(src->rows, src->columns);

  if ((*dest)->rows < src->rows || (*dest)->columns < src->columns)
    errx(EXIT_FAILURE, "Cannot copy: dest smaller than src");

  for (size_t i = 0; i < src->rows; i++) {
    memcpy((*dest)->data[i], src->data[i], src->columns * sizeof(int));
  }
}

void destroy(Board *p) {
  for (size_t i = 0; i < p->rows; i++) {
    free(p->data[i]);
  }

  free(p->data);
  free(p);
}
