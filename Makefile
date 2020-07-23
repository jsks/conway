SRC_FILES    := $(wildcard *.c)
HEADER_FILES := $(wildcard *.h)

OBJ_FILES    := $(SRC_FILES:%.c=%.o)

UNAME        := $(shell uname)

CFLAGS = -O2 -pipe -Wall -Wextra
LDFLAGS = -lncurses

all: conway
.PHONY: clean debug

ifeq ($(UNAME), Linux)
debug: CFLAGS += -fsanitize=address
endif

debug: CFLAGS += -O0 -g
debug: clean conway

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

conway: $(OBJ_FILES) $(HEADER_FILES)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ_FILES) -o $@

clean:
	rm -rf conway $(OBJ_FILES)
