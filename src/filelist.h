#ifndef __FILELIST_H
#define __FILELIST_H

/*
 * Structures
 */
typedef struct FileList FileList;
struct FileList
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
char *changePath(char *str1, char *str2);
int isDirectory(char *path);
void orderFileList(FileList *filelist);
FileList *getFileList(char *path);
void removeFileList(FileList *filelist);


#endif
