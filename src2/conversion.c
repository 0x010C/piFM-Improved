#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "conversion.h"

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
	newTask->tempPath = (char*) malloc(sizeof(char)*(5+i+5)); // /tmp/789.mov\0 : 5 + 3 + 5 chars
	strncpy(newTask->tempPath,"/tmp/",5);
	strncpy(newTask->tempPath+i+5,".mov",4);
	newTask->tempPath[i+9] = '\0';
	id = newTask->id;
	i += 4;
	do
	{
		newTask->tempPath[i--] = '0'+(id%10);
	}while((id/=10) != 0);

	/* Ajout à la fin de la liste */
	if(tasktowait == NULL)
		tasktowait = newTask;
	else
	{
		temp = tasktowait;
		while(temp->next != NULL)
			temp = temp->next;
		temp->next = newTask;
	}
	
	/* TODO: fork */
}
