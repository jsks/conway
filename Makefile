SRC_FILES    := $(wildcard src/*.c)
OBJ_FILES    := $(SRC_FILES:%.c=%.o)
DEPS         := $(OBJ_FILES:%.o=%.d)

CFLAGS = -O2 -g -Wall -Wextra -pipe
ifeq ($(shell uname), NetBSD)
	LDFLAGS = -lcurses
else
	LDFLAGS = -lncurses
endif

all: conway
.PHONY: clean fmt

-include $(DEPS)
%.o: %.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@

conway: $(OBJ_FILES)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ_FILES) -o $@

clean:
	rm -rf conway $(OBJ_FILES) $(DEPS)

fmt:
	clang-format -i --Werror --style=file src/*.c
