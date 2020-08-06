# Conway's Game of Life

A C implementation of Conway's Game of Life using ncurses.

### Getting Started

```sh
# Substitute `gmake` if on *BSD
$ make
$ ./conway
```

Press 'q' or CTRL-C to exit. A full list of keybindings can be displayed by pressing '?'.

`conway` can also read a starting position from a cells formated text file.

```sh
$ ./conway patterns/glider.cells
```
