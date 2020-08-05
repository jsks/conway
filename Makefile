SRC_FILES    := $(wildcard src/*.c)
HEADER_FILES := $(wildcard src/*.h)

OBJ_FILES    := $(SRC_FILES:%.c=%.o)

CFLAGS = -O2 -g -Wall -Wextra -pipe
LDFLAGS = -lncurses

all: conway
.PHONY: clean fmt

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

conway: $(OBJ_FILES) $(HEADER_FILES)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ_FILES) -o $@

clean:
	rm -rf conway $(OBJ_FILES)

fmt:
	clang-format -i --Werror --style=file src/*.c
