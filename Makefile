CC = gcc
CFLAGS = -Werror -Wextra -Wall -std=c99
DEBUG_FLAGS = -fsanitize=address -g

BIN = wordle

OBJS = $(addprefix src/, game.o main.o) $(addprefix src/utils/, alloc.o)

all: debug

wordle: $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN)

utils.o: src/utils/xalloc.c
	$(CC) $(CFLAGS) src/utils/xalloc.c -o src/utils/xalloc.o -c

debug: CFLAGS += $(DEBUG_FLAGS)
debug: wordle

clean:
	$(RM) $(BIN) $(OBJS)
