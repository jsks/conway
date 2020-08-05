#include <curses.h>
#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "board.h"
#include "conway.h"
#include "display.h"

unsigned int tick_ms = 128;

int main(int argc, char *argv[]) {
  srand(time(NULL));

  init_display();
  timeout(tick_ms);

  int height, width;
  getmaxyx(stdscr, height, width);

  Board *board = init_board(height, width);

  FILE *fp;
  if (argc > 1) {
    if (!(fp = fopen(argv[1], "r")))
      err(EXIT_FAILURE, NULL);

    load_file(fp, board);
    center(&board);
  } else {
    rpopulate(board, 0.3);
  }

  draw_board(board);
  bool paused = false;
  int ch;

  while (true) {
    switch ((ch = getch())) {
      case 'Q':
      case 'q':
        exit(EXIT_SUCCESS);
      case 'p':
      case 'P':
      case ' ':
        paused = !paused;
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

  return EXIT_SUCCESS;
}
