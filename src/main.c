#include <curses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "board.h"
#include "conway.h"
#include "display.h"
#include "misc.h"

unsigned int tick_ms = 128;

int main(int argc, char *argv[]) {
  srand(time(NULL));
  handle_signals();

  init_display();
  timeout(tick_ms);

  int height, width;
  getmaxyx(stdscr, height, width);

  Board *board = init_board(height, width);

  if (argc > 1) {
    FILE *fp;
    if (!(fp = fopen(argv[1], "r")))
      cerr(NULL);

    load_file(fp, &board);
  } else {
    rpopulate(board, 0.3);
  }

  draw_board(board);
  bool paused = false;

  while (true) {
    switch ((getch())) {
      case '?':
        help_popup();
        break;
      case 'Q':
      case 'q':
        quit();
      case 'p':
      case 'P':
      case ' ':
        if ((paused = !paused))
          timeout(-1);
        else
          timeout(tick_ms);
        break;
      case KEY_LEFT:
        inc_tick_ms();
        break;
      case KEY_RIGHT:
        dec_tick_ms();
        break;
      default:
        if (!paused) {
          tick(&board);
          draw_board(board);
        }
    }
  }

  quit();
}
