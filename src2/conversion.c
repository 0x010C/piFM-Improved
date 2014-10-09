#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <wait.h>
#include <pthread.h>
#include <signal.h>
#include <sys/types.h>

#include "conversion.h"

void co_init()
{
	/* Création du thread de conversion */
	pthread_create(&coThread, NULL, co_loop, (void*) NULL);
}

void *co_loop(void *notUsed)
{
	int i, nbRunningProcess = 0;
	TaskToWait *temp;
	siginfo_t status;

	while(param->sigEnd == False)
	{
		/* Mise en pause pour éviter une surcharge */
		sleep(param->timeBetweenTwoConverts);

		/* Recherche de nouveautés */
		for(i=0;i<playlist->nbFile;i++)
		{
			/* Si on trouve une musique nouvelle ajouté à la playlist, et qu'on a pas encore atteint la limite de processus */
			if(playlist->state[i] == 0 && (nbRunningProcess < param->maxRunningProcess || param->maxRunningProcess == 0))
			{
				/* Indication que cette musique est en train d'être converti */
				playlist->state[i] = 1;

				/* Comptage du nombre de processus actuellement en route */
				nbRunningProcess++;

				/* Lancment de la convertion */
				co_start(i, playlist->pathList[i]);
			}
		}

		/* Recherche de processus finis */
		temp = tasktowait;
		while(temp != NULL)
		{
			/* On vérifie si le processus de pid "temp->pid" a fini ou non */
			status.si_pid = 0;
			waitid(P_PID, temp->pid, &status, WEXITED | WNOHANG);
			
			/* S'il a fini */
			if(status.si_pid != 0)
			{
				/* On vérifie si le processus c'est fini correctement ou non */
				if(status.si_status == 0)
				{
					/* On enregistre le lien vers la musique converti dans la structure playlist */
					pl_updateEffList(temp->index, temp->tempPath);
					/* 2 = conversion effectué avec succes */
					playlist->state[temp->index] = 2;
				}
				else
					/* -1 = erreur dans la conversion */
					playlist->state[temp->index] = -1;

				/* Le processus étant fini, on peut le retirer de TaskToWait */
				co_remove(temp->index);

				/* Et on met à jour le compteur de processus actif */
				nbRunningProcess--;
			}
			temp = temp->next;
		}
	}
	co_end();

	return NULL;
}

void co_start(int id, char *realPath)
{
	int i, j;
	int  caractere;
	int devNull;
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
	id = param->absIndex;
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
	copyPath[i+10+strlen(realPath+j)] = '\0';

	id = param->absIndex;
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
				exit(42);
			if((newFile=fopen(copyPath, "wb")) == NULL)
			{
				fclose(oldFile);
				exit(43);
			}

			caractere = fgetc(oldFile);
			while(!feof(oldFile))
			{
				fputc(caractere, newFile);
				caractere = fgetc(oldFile);
			}

			fclose(newFile);
			fclose(oldFile);

			/* Redirection de STDOUT vers /dev/null */
			devNull = open("/dev/null", O_WRONLY);
			dup2(devNull, STDOUT_FILENO);
			dup2(devNull, STDERR_FILENO);

			/* Recouvrement pour la conversion */
			execlp("soundconverter","soundconverter", "-b", "-m", "audio/x-wav", "-s", ".wav", "-q", copyPath, NULL);
			exit(45);
			break;

		default:
			break;
	}

	param->absIndex++;
	free(copyPath);
}

void co_remove(int index)
{
	TaskToWait *temp = tasktowait;
	TaskToWait *prec = NULL;
	if(temp == NULL)
		return;
	while(temp->next != NULL && temp->index != index)
	{
		prec = temp;
		temp = temp->next;
	}
	if(temp->index == index)
	{
		free(temp->realPath);
		free(temp->tempPath);
		if(prec != NULL)
			prec->next = temp->next;
		else
			tasktowait = temp->next;
		free(temp);
	}
	return;
}

void co_fStop(int index)
{
	TaskToWait *temp = tasktowait;
	if(temp == NULL)
		return;
	while(temp->next != NULL && temp->index != index)
		temp = temp->next;
	if(temp->index == index)
		kill(temp->pid, SIGKILL);
	return;
}

void co_changeIndex(int oldIndex, int newIndex)
{
	TaskToWait *temp = tasktowait;
	while(temp->next != NULL && temp->index != oldIndex)
		temp = temp->next;
	if(temp->index == oldIndex)
		temp->index = newIndex;
}

void co_end()
{
	TaskToWait *temp = tasktowait;
	TaskToWait *next = NULL;
	if(temp == NULL)
		return;
	else
		next = temp->next;
	while(temp != NULL)
	{
		co_fStop(temp->index);
		free(temp->realPath);
		free(temp->tempPath);
		next = temp->next;
		free(temp);
		temp = next;
	}
	return;
}
