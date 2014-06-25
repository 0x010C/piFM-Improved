#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

#include "filelist.h"

char *changePath(char *str1, char *str2)
{
	if(strcmp(str2,".") == 0);

	else if(strcmp(str2,"..") == 0 && strcmp(str1,"/"))
	{
		str1[strlen(str1)-1] = '\0';
		int size = strlen(str1)-strlen(strrchr(str1,'/'));
		str1 = (char*) realloc(str1,sizeof(char)*(size+1));
		str1[size+1] = '\0';
	}

	else
	{
		str1 = (char*) realloc(str1, sizeof(char)*(strlen(str1)+strlen(str2)+2));
		strcat(str1,str2);
		strcat(str1,"/");
	}
	return str1;
}

int isDirectory(char *path)
{
	struct stat buf;

	stat(path,&buf);
	return S_ISDIR(buf.st_mode);
}

void orderFileList(FileList *filelist)
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

FileList *getFileList(char *path)
{
	FileList *filelist;
	DIR *descripteur;
	struct dirent *fileGetter;
	int count = 0,i;

	//ouverture du dossier
	descripteur = opendir(path);
	if(descripteur == NULL)
	{
		endwin();
		printf("Erreur d'ouverture du dossier '%s'",path);
		exit(1);
	}

	while((fileGetter = readdir(descripteur)) != NULL)
		count++;

	//création de la FileList
	filelist = (FileList*) malloc(sizeof(FileList));
	filelist->list = (char**) malloc(sizeof(char*)*count);
	filelist->nbFile = 0;

	rewinddir(descripteur);

	for(i=0;i<count;i++)
	{
		if((fileGetter = readdir(descripteur)) != NULL)
		{
			filelist->list[i] = (char*) malloc(sizeof(char)*strlen(fileGetter->d_name)+1);
			strcpy(filelist->list[i],fileGetter->d_name);
			filelist->list[i][strlen(fileGetter->d_name)] = '\0';
			filelist->nbFile++;
		}
	}

	closedir(descripteur);
	
	orderFileList(filelist);

	return filelist;
}

void removeFileList(FileList *filelist)
{
	while(filelist->nbFile > 0)
	{
		free(filelist->list[filelist->nbFile-1]);
		filelist->nbFile--;
	}
	free(filelist->list);
	free(filelist);
}
