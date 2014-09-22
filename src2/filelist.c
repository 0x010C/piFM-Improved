#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

#include "filelist.h"

void fl_init(char *path)
{
	DIR *rep;
	struct dirent *fileGetter;
	int count = 0, i = 0;

	/* Ouverture du dossier */
	rep = opendir(path);
	if(rep == NULL)
	{
		ev_end();
		printf("Erreur d'ouverture du dossier '%s'",path);
		exit(1);
	}

	while((fileGetter = readdir(rep)) != NULL)
		count++;

	/* Allocation et initialisation de la FileList */
	filelist = (FileList*) malloc(sizeof(FileList)*count);
	filelist->currentPath = (char*) malloc(sizeof(char)*(strlen(path)+1));
	filelist->list = (char**) malloc(sizeof(char*)*count);
	filelist->nbFile = count;
	strncpy(filelist->currentPath, path, strlen(path)+1);
	
	/* Remplissage de la liste de fichiers */
	rewinddir(rep);
	for(i=0;i < count;i++)
	{
		fileGetter = readdir(rep);
		/* Si c'est un dossier, on rajoute un slash à la fin du nom du fichier */
		if(isDirectory(fileGetter->d_name))
		{
			filelist->list[i] = (char*) malloc(sizeof(char)*(strlen(fileGetter->d_name)+2));
			strncpy(filelist->list[i], fileGetter->d_name, strlen(fileGetter->d_name));
			strncpy(filelist->list[i]+strlen(fileGetter->d_name), "/\0",2);
		}
		/* Sinon, on ajoute tel quel le nom du fichier */
		else
		{
			filelist->list[i] = (char*) malloc(sizeof(char)*(strlen(fileGetter->d_name)+1));
			strncpy(filelist->list[i], fileGetter->d_name, strlen(fileGetter->d_name));
			filelist->list[i][strlen(fileGetter->d_name)] = '\0';
		}
	}
	
	/* On finit par trier la liste et refermer le dossier */
	fl_order();
	closedir(rep);
}

int fl_compare(char *a, char *b) // TODO: Ne pas prendre en compte la casse dans le tri
{
	int i, A, B;
	
	/* Placage du dossier "./" avant "../" */
	if(strcmp(a,"./") == 0)
		return 0;
	if(strcmp(b,"./") == 0)
		return 1;
	
	/* Placage des dossiers avant les fichiers */
	if(a[strlen(a)-1] == '/' && b[strlen(b)-1] != '/')
		return -1;
	if(b[strlen(b)-1] == '/' && a[strlen(a)-1] != '/')
		return 1;
	
	/* Tri par ordre ascii */
	return strcmp(a, b);
}

void fl_order()
{
	int maxLen = 0, i = 0;
	Bool finTri = False;
	char *echange = NULL;
	
	/* Algorithme de tri par comparaisons successives */
	do
	{
		finTri = True;
		for(i=0;i<filelist->nbFile-1;i++)
		{
			if(fl_compare(filelist->list[i],filelist->list[i+1]) > 0)
			{
				echange = filelist->list[i];
				filelist->list[i] = filelist->list[i+1];
				filelist->list[i+1] = echange;
				finTri = False;
			}
		}
	} while(finTri == False);
}

Bool fl_changePath(int index)
{
	char *path = NULL;
	DIR *rep;
	int i;
	
	/* On verifie qu'il n'y ai pas d'erreur d'index */
	if(index >= 0 && index < filelist->nbFile)
	{
		/* Dans le cas du dossier "./", on ne fait rien */
		if(index == 0)
			return False;

		/* Dans le cas du dossier "../", on vérifie qu'on est pas dans le dossier "/" */
		else if(index == 1)
		{
			if(strcmp(filelist->currentPath,"/") != 0)
			{
				/* On détermine l'index de l'avant-dernier slash */
				i=strlen(filelist->currentPath)-2;
				while(filelist->currentPath[i] != '/')
					i--;

				/* On alloue la bonne quantité de mémoire et on y copie l'adresse jusqu'au-dit index */
				path = malloc(sizeof(char)*(i+2));
				strncpy(path, filelist->currentPath,i+1);
				path[i+1] = '\0';

				/* On libère la FileList puis on la recréé avec la nouvelle adresse */
				fl_end();
				fl_init(path);

				free(path);
				
				return True;
			}
			else
				return False;
		}
		else if(filelist->list[index][strlen(filelist->list[index]+1)] == '/')
		{
			/* On concatène l'adresse actuel et le nom du dossier */
			path = (char*) malloc(sizeof(char)*(strlen(filelist->currentPath)+strlen(filelist->list[index])+1));
			strncpy(path, filelist->currentPath, strlen(filelist->currentPath));
			strncpy(path+strlen(filelist->currentPath),filelist->list[index],strlen(filelist->list[index]));
			path[strlen(filelist->currentPath)+strlen(filelist->list[index])] = '\0';

			/* On libère la FileList puis on la recréé avec la nouvelle adresse */
			fl_end();
			fl_init(path);

			free(path);
			return True;
		}
	}
	return False;
}

void fl_end()
{
	int i;
	/* On libère toute la mémoire alloué pour la structure FileList */
	for(i=0;i<filelist->nbFile;i++)
		free(filelist->list[i]);
	free(filelist->list);
	free(filelist->currentPath);
	free(filelist);
}

Bool isDirectory(char *dir)
{
	struct stat buf;
	char *path = NULL;
	
	/* Allocation, puis concaténation de l'adresse courante et du nom du fichier à tester */
	path = (char*) malloc(sizeof(char)*(strlen(filelist->currentPath)+strlen(dir)+1));

	strncpy(path, filelist->currentPath, strlen(filelist->currentPath));
	strncpy(path+strlen(filelist->currentPath), dir, strlen(dir));
	strncpy(path+strlen(filelist->currentPath)+strlen(dir), "\0",1);

	/* Récupération des informations sur le fichier à tester */
	lstat(path,&buf);
	
	free(path);
	
	/* Et on vérifie si ce fichier est un dossier */
	if(S_ISDIR(buf.st_mode) == 0)
		return False;
	else
		return True;
}
