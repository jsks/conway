/*
 * 1. Any live cell with two or three live neighbours survives.
 * 2. Any dead cell with three live neighbours becomes a live cell.
 * 3. All other live cells die in the next generation. Similarly, all
 *    other dead cells stay dead.
 */

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "display.h"
#include "matrix.h"

#define NROWS 20
#define NCOLS 20

extern WINDOW *w;

enum State { RUNNING, PAUSED };

Board *run(Board *board) {
  Board *next_gen = copy(board);

  for (size_t i = 0; i < board->rows; i++) {
    for (size_t j = 0; j < board->columns; j++) {
      switch(neighbourhood_sum(board, (Coordinates) { i, j })) {
      case 3:
        next_gen->data[i][j] = 1;
        break;
      case 4:
        break;
      default:
        next_gen->data[i][j] = 0;
      }
    }
  }

  return next_gen;
}

void pause(int ms) {
  struct timespec req;
  req.tv_sec = 0;
  req.tv_nsec = 1000000 * ms;

  nanosleep(&req, NULL);
}

int main(void) {
  srand(time(NULL));

  int ms = 100;

  init_display();

  Board *board = new_board(40, 80);
  random_populate(board, .2);

  int ch;
  enum State state = RUNNING;
  while (1) {
    switch ((ch = wgetch(w))) {
      case 'q':
        exit(0);
      case ' ':
        state = (state == RUNNING) ? PAUSED : RUNNING;
        break;
      case KEY_LEFT:
        ms += 100;
        break;
      case KEY_RIGHT:
        ms -= 100;
        ms += 10;
        break;
    }

    if (state == PAUSED) {
      pause(ms);
      continue;
    }

    print(board);
    board = run(board);

    pause(ms);
  }

  destroy(board);
  return 0;
}
