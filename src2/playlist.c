#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

void pl_add(char *path, char *file)
{
	int i;

	/* Vérification que l'entrée à ajouter n'est pas déjà présente */
	for(i=0;i<playlist->nbFile;i++)
		if(strncmp(playlist->pathList[i], path, strlen(path)) == 0 && strcmp(playlist->displayList[i], file) == 0)
			return;

	/* Allocation des cases de tableau supplémentaire */
	if(playlist->displayList == NULL)
	{
		playlist->displayList = (char**) malloc(sizeof(char*));
		playlist->pathList = (char**) malloc(sizeof(char*));
	}
	else
	{
		playlist->displayList = (char**) realloc(playlist->displayList, sizeof(char*)*(playlist->nbFile+1));
		playlist->pathList = (char**) realloc(playlist->pathList, sizeof(char*)*(playlist->nbFile+1));
	}

	/* Allocation des 2 nouvelles chaines de caractères */
	playlist->displayList[playlist->nbFile] = (char*) malloc(sizeof(char)*(strlen(file)+1));
	playlist->pathList[playlist->nbFile] = (char*) malloc(sizeof(char)*(strlen(path)+strlen(file)+1));

	/* Copie des valeurs dans le tableau */
	strncpy(playlist->displayList[playlist->nbFile],file,strlen(file));
	playlist->displayList[playlist->nbFile][strlen(file)] = '\0';
	strncpy(playlist->pathList[playlist->nbFile],path,strlen(path));
	strncpy(playlist->pathList[playlist->nbFile]+strlen(path),file,strlen(file));
	playlist->pathList[playlist->nbFile][strlen(path)+strlen(file)] = '\0';

	/* Enregistrement du nouveau nombre de fichiers */
	playlist->nbFile++;
}

void pl_addAll(int index)
{
	int i;
	
	if(fl_changePath(index))
	{
		for(i=2;i<filelist->nbFile;i++) /* On commence à deux, rien ne sert de tester à chaque fois  ./ et ../  */
			if(isMusic(filelist->list[i]))
				pl_add(filelist->currentPath, filelist->list[i]);
		fl_changePath(1);
	}
}

void pl_remove(int index) /* TODO: Debug, ca supprime par packets au lieu de juste un */
{
	int i;
	
	if(index >= 0 && index < playlist->nbFile)
	{
		free(playlist->displayList[index]);
		free(playlist->pathList[index]);
		for(i=index;i<playlist->nbFile-1;i++)
		{
			playlist->displayList[i] = playlist->displayList[i+1];
			playlist->pathList[i] = playlist->pathList[i+1];
		}
		playlist->nbFile--;
		playlist->displayList = (char**) realloc(playlist->displayList, sizeof(char*)*playlist->nbFile--);
		playlist->pathList = (char**) realloc(playlist->pathList, sizeof(char*)*playlist->nbFile--);
	}
}

void pl_removeAll()
{
	int i;

	if(playlist->displayList != NULL)
	{
		for(i=0;i<playlist->nbFile;i++)
		{
			free(playlist->displayList[i]);
			free(playlist->pathList[i]);
		}
		playlist->nbFile = 0;
		free(playlist->displayList);
		free(playlist->pathList);
		playlist->displayList = NULL;
		playlist->pathList = NULL;
	}
	
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

