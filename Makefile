CC=gcc
CFLAGS=-Wall
EXEC=spellchecker

all: $(EXEC)

spellchecker: words_functions.o main.o
	$(CC) -o spellchecker words_functions.o main.o

words_functions.o: words_functions.c
	$(CC) -o words_functions.o -c words_functions.c $(CFLAGS)

main.o: main.c words_functions.h
	$(CC) -o main.o -c main.c $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
