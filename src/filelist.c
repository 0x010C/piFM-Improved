#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

#include "filelist.h"

void fl_changePath(char *newDir)
{
	char *newPath = NULL;
	
	if(strcmp(newDir,"./") == 0 || (strcmp(newDir,"../") == 0 && strcmp(filelist->currentPath,"/") == 0));

	else if(strcmp(newDir,"../") == 0)
	{
		filelist->currentPath[strlen(filelist->currentPath)-1] = '\0';
		int size = strlen(filelist->currentPath)-strlen(strrchr(filelist->currentPath,'/'));
		newPath = malloc(sizeof(char)*(size+1));
		strncpy(newPath,filelist->currentPath,size);
		newPath[size] = '\0';
		
		fl_end();
		fl_init(newPath);
	}

	else
	{
		newPath = (char*) malloc(sizeof(char)*(strlen(filelist->currentPath)+strlen(newDir)+2));
		strncpy(newPath,filelist->currentPath,strlen(filelist->currentPath));
		newPath[strlen(filelist->currentPath)] = '\0';
		strcat(newPath,newDir);
		
		fl_end();
		fl_init(newPath);
	}
	
}

Bool isDirectory(char *path)
{
	struct stat buf;

	stat(path,&buf);
	return S_ISDIR(buf.st_mode);
}

void fl_order()
{
	int i = 0;
	int fin_tri = 0;
	char echange[256]; // un fichier fait au max 255 caracteres
	do
	{
		fin_tri = 1;
		for(i=0;i<filelist->nbFile-1;i++)
		{
			if(strcmp(filelist->list[i],filelist->list[i+1]) > 0)
			{
				strcpy(echange,filelist->list[i]);
				strcpy(filelist->list[i],filelist->list[i+1]);
				strcpy(filelist->list[i+1],echange);
				fin_tri = 0;
			}
		}
	} while(fin_tri == 0);
}

void fl_init(char *path)
{
	DIR *rep;
	struct dirent *fileGetter;
	int count = 0,i;

	//ouverture du dossier
	rep = opendir(path);
	if(rep == NULL)
	{
		endwin();
		printf("Erreur d'ouverture du dossier '%s'",path);
		exit(1);
	}

	while((fileGetter = readdir(rep)) != NULL)
		count++;

	//création de la FileList
	filelist = (FileList*) malloc(sizeof(FileList));
	filelist->currentPath = path;
	filelist->list = (char**) malloc(sizeof(char*)*count);
	filelist->nbFile = 0;

	rewinddir(rep);

	for(i=0;i<count;i++)
	{
		if((fileGetter = readdir(rep)) != NULL)
		{
			if(isDirectory(fileGetter->d_name) == True)
			{
				filelist->list[i] = (char*) malloc(sizeof(char)*(strlen(fileGetter->d_name)+2));
				strcpy(filelist->list[i],fileGetter->d_name);
				filelist->list[i][strlen(fileGetter->d_name)] = '/';
				filelist->list[i][strlen(fileGetter->d_name)+1] = '\0';
			}
			else
			{
				filelist->list[i] = (char*) malloc(sizeof(char)*(strlen(fileGetter->d_name)+1));
				strcpy(filelist->list[i],fileGetter->d_name);
				filelist->list[i][strlen(fileGetter->d_name)] = '\0';
			}
			filelist->nbFile++;
		}
	}

	closedir(descripteur);
	
	fl_order();
}

void fl_end()
{
	while(filelist->nbFile > 0)
	{
		free(filelist->list[filelist->nbFile-1]);
		filelist->nbFile--;
	}
	free(filelist->list);
	free(filelist->currentPath);
	free(filelist);
}
