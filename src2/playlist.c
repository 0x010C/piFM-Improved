#include <stdlib.h>
#include <stdio.h>

#include "playlist.h"

void pl_init()
{
	if(playlist == NULL)
	{
		playlist = (PlayList*) malloc(sizeof(PlayList));
		playlist->nbFile = 0;
		playlist->displayList = NULL;
		playlist->pathList = NULL;
	}
}

void pl_add(char *filePath)
{

}

void pl_addAll(char *filePath)
{

}

void pl_remove(int index)
{

}

void pl_removeAll()
{

}

int pl_count()
{

}

void pl_end()
{
	int i;

	if(playlist != NULL)
	{
		if(playlist->displayList != NULL)
		{
			for(i=0;i<playlist->nbFile;i++)
			{
				free(playlist->displayList[i]);
				free(playlist->pathList[i]);
			}
			free(playlist->displayList);
			free(playlist->pathList);
		}
		free(playlist);
		playlist = NULL;
	}
}

