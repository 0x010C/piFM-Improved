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
void pl_end();


#endif
