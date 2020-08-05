#ifndef _display_h
#define _display_h

#include <curses.h>
#include "board.h"

void init_display(void);
WINDOW *create_win(int, int, int, int, char *);
void draw_board(Board *);
void update_toolbox(unsigned int);

#endif
