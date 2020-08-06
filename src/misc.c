#include <curses.h>
#include <err.h>
#include <signal.h>
#include <stdlib.h>

void quit(void) {
  endwin();
  exit(EXIT_SUCCESS);
}

void cerr(const char *fmt, ...) {
  endwin();

  va_list args;

  va_start(args, fmt);
  verr(EXIT_FAILURE, fmt, args);
  va_end(args);
}

void cerrx(const char *fmt, ...) {
  endwin();

  va_list args;

  va_start(args, fmt);
  verrx(EXIT_FAILURE, fmt, args);
  va_end(args);
}

void handler(int sig) {
  switch (sig) {
    case SIGTERM:
    case SIGINT:
      quit();
    case SIGWINCH:
      cerrx("Unable to resize terminal");
  }
}

void handle_signals(void) {
  struct sigaction act;

  act.sa_handler = handler;
  act.sa_flags = 0;
  sigemptyset(&act.sa_mask);

  sigaction(SIGTERM, &act, NULL);
  sigaction(SIGINT, &act, NULL);
  sigaction(SIGWINCH, &act, NULL);
}
