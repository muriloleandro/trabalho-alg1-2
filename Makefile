CC := gcc
DEBUG := -ggdb3 -Og
CFLAGS := -std=c99 -Wall # $(DEBUG)

SRC := $(wildcard src/*.c)
OBJ := $(SRC:src/%.c=obj/%.o)

.PHONY: all run clean valgrind zip relatorio

all: bin/main

bin/main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

run:
	./bin/main

clean:
	rm obj/*.o
	rm bin/*

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./bin/main

zip:
	if test -f "Murilo_Glauco.zip"; then rm Murilo_Glauco.zip; fi
	zip -r Murilo_Glauco.zip . -x '*.git*' -x 'bin/main' -x 'obj/*.o' -x 'valgrind-out.txt'

relatorio:
	pdflatex -output-directory=relatorio relatorio/relatorio.tex