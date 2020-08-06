#include <curses.h>
#include <stdbool.h>
#include <stdlib.h>

#include "display.h"

void init_display(void) {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, true);

  curs_set(0);
}

void draw_board(Board *board) {
  for (size_t i = 0; i < board->rows; i++) {
    move(i, 1);

    for (size_t j = 0; j < board->columns; j++) {
      printw("%c", (isset(board, Cpair(i, j))) ? '#' : ' ');
    }
  }

  refresh();
}
