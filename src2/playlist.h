#ifndef __PLAYLIST_H
#define __PLAYLIST_H


/*
 * Structures
 */
typedef struct PlayList PlayList;
struct PlayList
{
	int nbFile;
	char **displayList;
	char **pathList;
	char **effList;
	int *state; /* 0: non-traité | 1: en cours de traitement | 2: traité | -1: erreur */
};


/*
 * Includes
 */
#include "main.h"


/*
 * Functions' header
 */
void pl_init();
void pl_add(char *path, char *file);
void pl_addAll();
void pl_remove(int index);
void pl_removeAll();
void pl_updateEffList();
void pl_end();


#endif
