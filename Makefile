CC=cc

all:
	$(CC) -o main main.c -ggdb -lm
clear:
	rm -rf main core.*
