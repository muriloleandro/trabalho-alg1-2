CC := gcc
DEBUG := -ggdb3 -Og
CFLAGS := -std=c99 -Wall # $(DEBUG)

SRC := $(wildcard src/*.c)
OBJ := $(SRC:src/%.c=obj/%.o)

.PHONY: all run clean valgrind zip

all: bin/main

bin/main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

run:
	./bin/main

clean:
	rm obj/* bin/*

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./bin/main

zip:
	if test -f "source.zip"; then rm source.zip; fi
	zip source.zip Makefile src/* bin obj
