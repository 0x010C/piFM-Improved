#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "launchpifm.h"

void lp_start()
{
	if(lpThread != 0)
		lp_stop();
	pthread_create(&lpThread, NULL, lp_loop, (void*) NULL);
}

void lp_loop()
{
	if(playedIndex < 0 || param->playedIndex >= playlist->nbFile)
		return;
	do
	{
		if(plPID != 0)
			kill(plPID, SIGCONT);
		else
		{
			switch(plPID=fork())
			{
				case -1:
					plPID = 0;
					exit(1);
					break;
				case 0:
					execlp("vlc", "vlc", playlist->effList[param->playedIndex], NULL);
					exit(2);
					break;
			}
		}
		
		/* TODO */

		param->playedIndex++;
	} while(param->playedIndex < playlist->nbFile)
	param->playedIndex = -1;
}

void lp_pause()
{

}

void lp_ontinue()
{
s
}

void lp_stop()
{

}

