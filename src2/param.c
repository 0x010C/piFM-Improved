#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "param.h"


void pa_init()
{
	if(param == NULL)
	{
		param = (Param*) malloc(sizeof(Param));
		param->frequence = 1000;
		param->playedIndex = -1;
		param->mode = mo_file;
		param->sigEnd = False;
		param->absIndex = 1;
		param->maxRunningProcess = 4;
		param->timeBetweenTwoConverts = 1;
	}
}

void pa_parse(int argc, char **argv)
{
	int i;
	int f=0;

	/* On initialise la variable global param */
	if(param == NULL)
		pa_init();
	
	/* On analyse chaque arguments un par un */
	for(i=0;i<argc;i++)
	{
		/* Si le paramètre est "-f" */
		if(strcmp(argv[i],"-f") == 0 && i+1<argc)
		{
			i++;
			f = strtof(argv[i],NULL)*10;
			if(f >= 875 && f <= 1080)
				param->frequence = f;
		}
	}
}

void pa_end()
{
	if(param != NULL)
	{
		free(param);
		param = NULL;
	}
}

