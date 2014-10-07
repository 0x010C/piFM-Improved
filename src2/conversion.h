#ifndef __CONVERSION_H
#define __CONVERSION_H


/*
 * Structures
 */
typedef struct TaskToWait TaskToWait;
struct TaskToWait
{
	int id;
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
void co_start(int id, char *realPath);
void co_check();
void co_remove();
void co_end();


#endif
