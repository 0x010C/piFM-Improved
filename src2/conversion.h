#ifndef __CONVERSION_H
#define __CONVERSION_H


/*
 * Structures
 */
typedef struct TaskToWait TaskToWait;
struct TaskToWait
{
	int index;
	int pid;
	char *realPath;
	char *tempPath;
	TaskToWait *next;
};


/*
 * Includes
 */
#include "main.h"


/*
 * Functions' header
 */
void co_init();
void *co_loop(void *notUsed);
void co_start(int id, char *realPath);
void co_remove(int index);
void co_fStop(int index);
void co_changeIndex(int oldIndex, int newIndex);
void co_end();


#endif
