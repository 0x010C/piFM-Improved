#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <pthread.h>

#include "conversion.h"

void co_init()
{
	/* Création du thread de conversion */
	pthread_create(coThread, NULL, co_loop, NULL);
}

void *co_loop(void *notUsed)
{
	while(param->sigEnd == False)
	{
		/* Mise en pause pour éviter une surcharge */
		sleep(1);
		/* ... */
	}
	return NULL;
}

void co_start(int id, char *realPath)
{
	int i, j;
	int  caractere;
	FILE *oldFile = NULL;
	FILE *newFile = NULL;
	TaskToWait *newTask = NULL;
	TaskToWait *temp = NULL;
	char *copyPath = NULL;

	/* Allocation de la structure */
	newTask = (TaskToWait*) malloc(sizeof(TaskToWait));

	/* Init de id et de next*/
	newTask->index = id;
	newTask->next = NULL;

	/* Allocation et remplissage du chemin effectif */
	newTask->realPath = (char*) malloc(sizeof(char)*(strlen(realPath)+1));
	strncpy(newTask->realPath,realPath,strlen(realPath));
	newTask->realPath[strlen(realPath)] = '\0';

	/* Allocation du chemin vers le fichier converti */
	for(i=1;(id/=10) != 0;i++);
	newTask->tempPath = (char*) malloc(sizeof(char)*(10+i+5)); /* /tmp/pifm-789.mov\0 : 10 + 3 + 5 chars */

	/* Allocation du chemin vers la destination de la copie initial */
	j=strlen(realPath)-1;
	while(realPath[j] != '.' && j > 0)
		j--;
	copyPath = (char*) malloc(sizeof(char)*(10+i+strlen(realPath+j)+1));

	/* Remplissage des deux chemins */
	strncpy(newTask->tempPath, "/tmp/pifm-", 10);
	strncpy(newTask->tempPath+10+i, ".mov", 4);
	newTask->tempPath[i+14] = '\0';

	strncpy(copyPath, "/tmp/pifm-", 10);
	strncpy(copyPath+10+i, realPath+j, strlen(realPath+j));
	copyPath[i+10+j] = '\0';

	id = newTask->index;
	i += 9;
	do
	{
		copyPath[i] = '0'+(id%10);
		newTask->tempPath[i--] = '0'+(id%10);
	}while((id/=10) != 0);

	/* Ajout à la fin de la liste chainée */
	if(tasktowait == NULL)
		tasktowait = newTask;
	else
	{
		temp = tasktowait;
		while(temp->next != NULL)
			temp = temp->next;
		temp->next = newTask;
	}

	/* Fork */
	switch(newTask->pid = fork())
	{
		/* Si le fork échoue */
		case -1:
			fprintf(stderr,"Erreur de fork");
			ev_end();
			break;
			
		case 0:
			/* Copie du fichier vers /tmp/ */
			if((oldFile = fopen(realPath, "rb")) == NULL)
				exit(-1);
			if((newFile=fopen(copyPath, "wb")) == NULL)
			{
				fclose(oldFile);
				exit(-2);
			}

			caractere = fgetc(oldFile);
			while(!feof(oldFile))
			{
					fputc(caractere, newFile);
					caractere = fgetc(oldFile);
			}

			fclose(newFile);
			fclose(oldFile);

			/* Recouvrement pour la conversion */
			execlp("soundconverter","soundconverter", "-b", "-m", "audio/x-wav", "-s", ".wav", "-q", copyPath, NULL);
			exit(-42);
			break;

		default:
			break;
	}
fprintf(stderr,"p");
fflush(stderr);
	free(copyPath);
}

void co_remove(int index)
{
	return;
}

void co_fStop(int index)
{
	return;
}

void co_changeIndex(int oldIndex, int newIndex)
{
	return;
}

void co_end()
{
	return;
}
