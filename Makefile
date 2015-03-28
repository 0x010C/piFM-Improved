## Compilateur
CC=gcc
FLAGS=-Wall -Werror -pedantic -fpic
LIB=-lncurses -pthread
# Main
EXE=pifmp


# Génère l'ensemble du projet
all:
	$(CC) $(FLAGS) src/main.c src/conversion.c src/display.c src/event.c src/filelist.c src/launchpifm.c src/param.c src/playlist.c -o ./$(EXE) $(LIB)
