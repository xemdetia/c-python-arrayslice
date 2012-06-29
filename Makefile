
CC=gcc
OUT=-o
all: ints main

main: main.c arrayslice.c
	$(CC) main.c arrayslice.c -ggdb $(OUT)main
ints: ints.c arrayslice.c
	$(CC) ints.c arrayslice.c -ggdb $(OUT)ints