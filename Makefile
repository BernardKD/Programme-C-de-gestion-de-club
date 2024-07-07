CC = gcc
CFLAGS = -Wall -Wextra
OBJECTS = main.o projet.o -lm

all: main

main: $(OBJECTS)
	$(CC) $(CFLAGS) -o main $(OBJECTS)

main.o: main.c projet.h
	$(CC) $(CFLAGS) -c main.c

projet.o: projet.c projet.h
	$(CC) $(CFLAGS) -c projet.c

clean:
	rm -f main $(OBJECTS)
