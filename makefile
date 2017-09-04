
#This is just a basic makefile for compilation. both Allegro 5.x.x and LibSodium will be required to properly compile.

CFLAGS = `pkg-config --cflags --libs allegro-5 allegro_primitives-5 allegro_font-5 allegro_ttf-5` -L. -lsodium
CFILES = src/main.c src/scenes.c src/char.c src/item.c src/helpers.c
CC = gcc

all: 
	$(CC) -Wl,-rpath . $(CFILES) -o rpg $(CFLAGS)

