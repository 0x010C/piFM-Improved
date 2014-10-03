#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "playlist.h"

void co_start(int id, char *realPath)
{
	int i, temp = id;
	TaskToWait *newTask = NULL;
	newTask = (TaskToWait*) malloc(sizeof(TaskToWait));
	newTask->realPath = (char*) malloc(sizeof(char)*(strlen(realPath)+1);
	for(i=1;(temp/=10) != 0;i++);
	newTask->tempPath = (char*) malloc(sizeof(char)*(5+i+5)); // /tmp/789.mov\0 : 5 + 3 + 5 chars
}
