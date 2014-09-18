#ifndef __PLAYLIST_H
#define __PLAYLIST_H


/*
 * Structures
 */
typedef struct PlayList PlayList;
struct PlayList
{
	int nbFile;
	char **list;
};

/*
 * Includes
 */
#include "main.h"


/*
 * Functions' header
 */
void pl_init();
void pl_add(char *filePath);
void pl_addAll(char *filePath);
void pl_remove(int index);
void pl_removeAll();
int pl_count();
void pl_end();


#endif
