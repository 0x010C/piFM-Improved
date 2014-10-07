#include <stdlib.h>
#include <stdio.h>
#include <wait.h> /* Pour test */
#include <sys/types.h>

#include "main.h"

void T()
{
	int i=0;
	FILE *file = NULL;
	file = fopen("trace.log","a+");

	fprintf(file,"=============================================\n\n");

	fprintf(file,"filelist->nbFile : %d#\n",filelist->nbFile);
	fprintf(file,"filelist->currentPath : %s#\n",filelist->currentPath);
	for(i=0;i<filelist->nbFile;i++)
		fprintf(file,"filelist->list[%d] : %s#\n",i,filelist->list[i]);

	fprintf(file,"\nparam->frequence : %d#\n", param->frequence);
	fprintf(file,"param->playedIndex : %d#\n", param->playedIndex);
	fprintf(file,"param->mode : %d#\n\n", param->mode);

	fprintf(file,"=============================================\n\n");

	fclose(file);
}

void test()
{
	/*
	ev_init();
	co_start(721, "/home/kiwi/Bureau/01-GypsyCab.mp3");
	waitid(P_PID, tasktowait->pid, &ttt, WEXITED);
	fprintf(stderr,"%d,%d",ttt.si_status,ttt.si_pid);
	ev_end();*/
}

int main(int argc, char **argv)
{
#ifndef __TEST__
	/* Initialisation des variables globales */
	siginfo_t ttt;
	playlist = NULL;
	filelist = NULL;
	param = NULL;
	tasktowait = NULL;
	coThread = NULL;
	
	/* Parsage des arguments */
	pa_parse(argc, argv);
	
	/* Début de la boucle de gestion des évènements */
	ev_loop();
	co_start(327, "/home/kiwi/Bureau/01-GypsyCab.mp3");
	waitid(P_PID, tasktowait->pid, &ttt, WEXITED);
	fprintf(stderr,"%d,%d",ttt.si_status,ttt.si_pid);
#else
	test();
#endif
	return 0;
}

/*
TODO:

*/
