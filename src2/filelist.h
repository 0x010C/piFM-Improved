#ifndef __FILELIST_H
#define __FILELIST_H

/*
 * Structures
 */
typedef struct FileList FileList;
struct FileList
{
	int nbFile;
	char *currentPath;
	char **list;
};


/*
 * Includes
 */
#include "main.h"


/*
 * Functions' header
 */
void fl_init();
Bool fl_changePath(int index);
void fl_order();
void fl_end();

Bool isDirectory(char *path);
Bool isMusic(char *path);


#endif
