#ifndef _conway_h
#define _conway_h

#include <stdio.h>

#include "board.h"

extern unsigned int tick_ms;

#define inc_tick_ms() {                             \
  tick_ms = (tick_ms == 1024) ? 1024 : tick_ms * 2; \
  timeout(tick_ms);                                 \
}                                                   \

#define dec_tick_ms() {                         \
  tick_ms = (tick_ms == 16) ? 16 : tick_ms / 2; \
  timeout(tick_ms);                             \
}                                               \

void load_file(FILE *, Board *);
void tick(Board **board);

#endif
