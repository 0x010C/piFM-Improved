#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "conversion.h"

void co_init()
{

}

void co_start(int id, char *realPath)
{
	int i;
	TaskToWait *newTask = NULL;
	TaskToWait *temp = NULL;
	
	/* Allocation de la structure */
	newTask = (TaskToWait*) malloc(sizeof(TaskToWait));
	
	/* Init de id et de next*/
	newTask->id = id;
	newTask->next = NULL;
	
	/* Allocation et remplissage du chemin effectif */
	newTask->realPath = (char*) malloc(sizeof(char)*(strlen(realPath)+1));
	strncpy(newTask->realPath,realPath,strlen(realPath));
	newTask->realPath[strlen(realPath)] = '\0';
	
	/* Allocation et remplissage du chemin vers le fichier converti */
	for(i=1;(id/=10) != 0;i++);
	newTask->tempPath = (char*) malloc(sizeof(char)*(10+i+5)); /* /tmp/pifm-789.mov\0 : 5 + 3 + 5 chars */
	strncpy(newTask->tempPath,"/tmp/pifm-",10);
	strncpy(newTask->tempPath+10+i,".mov",4);
	newTask->tempPath[i+14] = '\0';
	id = newTask->id;
	i += 9;
	do
	{
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
			/* Lbération de la mémoire */
			ev_end();

			/* Recouvrement pour la conversion */
			execlp("ffmpeg","ffmpeg", "-v", "0", "-i", newTask->realPath, "-f", "s16le", "-ar", "22.05k", "-ac", "1", newTask->tempPath, NULL);
			exit(-2);
			break;

		default:
			
			break;
	}
}
