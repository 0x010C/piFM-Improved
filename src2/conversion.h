#ifndef __CONVERSION_H
#define __CONVERSION_H


/*
 * Structures
 */
typedef struct taskToWait;
struct 
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
void co_init(char *);
void co_check();


#endif
