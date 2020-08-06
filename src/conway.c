#include <stdlib.h>
#include <sys/types.h>

#include "conway.h"
#include "misc.h"

void load_file(FILE *fp, Board **board) {
  ssize_t len;
  size_t bufsize = 0, nlines = 0;
  char *line = NULL;

  while ((len = getline(&line, &bufsize, fp)) > 0) {
    if (line[0] == '!')
      continue;

    for (size_t i = 0; i < (size_t) len; i++) {
      if (i == (*board)->columns)
        cerrx("Pattern too wide for current terminal");

      if (line[i] == 'O')
        set(*board, Cpair(nlines, i));
    }

    if (++nlines == (*board)->rows)
      cerrx("Pattern too long for current terminal");
  }

  if (len == -1 && !feof(fp))
    cerr(NULL);

  // Adjust starting position to be centered in screen
  center(board);

  free(line);
}

void tick(Board **board) {
  // Rules:
  //   1. Any live cell with two or three live neighbours survives.
  //   2. Any dead cell with three live neighbours becomes a live
  //      cell.
  //   3. All other live cells die in the next generation. Similarly,
  //      all other dead cells stay dead.

  static Board *next_gen = NULL;
  copy(*board, &next_gen);

  for (size_t i = 0; i < (*board)->rows; i++) {
    for (size_t j = 0; j < (*board)->columns; j++) {
      switch (neighbourhood_sum(*board, Cpair(i, j))) {
        case 3:
          set(next_gen, Cpair(i, j));
          break;
        case 4:
          break;
        default:
          unset(next_gen, Cpair(i, j));
      }
    }
  }

  Board *tmp = *board;
  *board = next_gen;
  next_gen = tmp;
}
