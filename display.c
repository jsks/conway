#include <ncurses.h>
#include <stdio.h>

#include "display.h"
#include "matrix.h"

WINDOW *w;

void cleanup(void) {
  endwin();
}

void init_display(void) {
  initscr();
  cbreak();
  noecho();

  curs_set(0);

  int height, width;
  getmaxyx(stdscr, height, width);

  WINDOW *toolbox = newwin(3, width, height - 3, 5);
  wprintw(toolbox, "q: quit, <space>: pause, <left>: slowdown, <right>: speedup\n");
  wrefresh(toolbox);

  w = newwin(height - 3, width, 0, 0);
  nodelay(w, true);
  keypad(w, true);

  atexit(cleanup);
}

void print(Board *board) {
  for (size_t i = 0; i < board->rows; i++) {
    wmove(w, i + 2, 3);

    for (size_t j = 0; j < board->columns; j++) {
      wprintw(w, "%c", (get(board, (Coordinates) { i, j }) == 1) ? '#' : ' ');
    }
  }

  wrefresh(w);
}
