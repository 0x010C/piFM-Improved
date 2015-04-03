#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <wait.h>
#include <pthread.h>
#include <signal.h>
#include <sys/types.h>

#include "launchpifm.h"

void lp_start()
{
	pthread_attr_t attr;

	if(lpPID != 0)
		lp_stop();
	if(lpThread == 0 && lpPID == 0)
	{
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

		pthread_create(&lpThread, &attr, lp_loop, (void*) NULL);
	}
}

void lp_continue()
{
	pthread_attr_t attr;

	if(lpThread == 0 && lpPID != 0)
	{
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

		pthread_create(&lpThread, &attr, lp_loop, (void*) NULL);
	}
}

void *lp_loop(void *notUsed)
{
	siginfo_t status;
	char *buffer;
	int devNull;

	if(param->playedIndex < 0 || param->playedIndex >= playlist->nbFile)
		pthread_exit("2");
	while(playlist->state[param->playedIndex] == 0 || playlist->state[param->playedIndex] == 1)
		sleep(param->timeBetweenTwoConverts);
	if(playlist->state[param->playedIndex] == -1)
		pthread_exit("3");
		
	do
	{
		if(lpPID != 0)
			kill(lpPID, SIGCONT);
		else
		{
			switch(lpPID=fork())
			{
				case -1:
					lpPID = 0;
					exit(1);
					break;
				case 0:
					/* Redirection de STDOUT et de STDERR vers /dev/null */
					devNull = open("/dev/null", O_WRONLY);
					dup2(devNull, STDOUT_FILENO);
					dup2(devNull, STDERR_FILENO);
					#ifdef TEST
					execlp("cvlc", "cvlc", "--play-and-exit", playlist->effList[param->playedIndex], NULL);
					#else
					buffer = (char*) malloc(sizeof(char)*7);
					sprintf(buffer, "%.2f", param->frequence);
					execlp("pifm", "pifmp", playlist->effList[param->playedIndex], buffer, NULL);
					free(buffer);
					#endif
					exit(2);
					break;
			}
		}
		
		waitid(P_PID, lpPID, &status, WEXITED | WSTOPPED | WCONTINUED);
		if(status.si_signo == SIGCHLD)
		{
			switch(status.si_code)
			{
				case CLD_EXITED:
					lpPID = 0;
					param->playedIndex++;
					break;
				case CLD_KILLED:
					lpPID = 0;
					lpThread = 0;
					pthread_exit(0);
					break;
				case CLD_STOPPED:
					lpThread = 0;
					pthread_exit(0);
					break;
			}
		}
		else
		{
			lpPID = 0;
			lpThread = 0;
			pthread_exit("1");
		}

	} while(param->playedIndex < playlist->nbFile);
	param->playedIndex = -1;
	pthread_exit("0");
}

void lp_pause()
{
	if(lpThread != 0 && lpPID != 0)
		kill(lpPID, SIGSTOP);
}

void lp_stop()
{
	if(lpPID != 0)
		kill(lpPID, SIGKILL);
	lpPID = 0;
	lpThread = 0;
	param->playedIndex = -1;
}

