#ifndef _misc_h
#define _misc_h

#include <stdarg.h>

void quit(void);
void cerr(const char *, ...);
void cerrx(const char *, ...);
void handle_signals(void);

#endif
