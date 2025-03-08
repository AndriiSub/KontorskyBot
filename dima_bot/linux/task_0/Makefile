CC=gcc
CFLAGS=-Wall -std=c99

all: main

main: src/main.o
	$(CC) $(CFLAGS) src/main.o -o bin/main

src/main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o

clean:
	rm -f src/*.o bin/main
