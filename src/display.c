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

void help_popup(void) {
  extern unsigned int tick_ms;
  timeout(-1);

  int height, width;
  getmaxyx(stdscr, height, width);

  WINDOW *popup = newwin(7, 46, (height - 7) / 2, (width - 46) / 2);
  mvwprintw(popup, 1, 1,
            "Keybindings:\n"
            "\tq, Q\t\t Quit\n"
            "\tp, P, <space>\t Pause\n"
            "\t<KEY_LEFT>\t Decrease tick delay\n"
            "\t<KEY_RIGHT>\t Increase tick delay\n");

  box(popup, 0, 0);
  wrefresh(popup);

  wgetch(popup);
  delwin(popup);

  touchwin(stdscr);
  refresh();
  timeout(tick_ms);
}
