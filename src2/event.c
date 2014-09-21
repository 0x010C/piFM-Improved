#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <string.h>

#include "main.h"

void ev_break()
{
	getchar();
}

void ev_init()
{
	di_init();
	fl_init("/");
	di_updateBoxing("/","Playlist");
	di_updateFilelist(0,0);
	di_refresh();
}

int ev_loop()
{
	int touche = ' ';
	int index = 0;
	char *title = NULL;

	ev_init();
	while((touche=getch()) != 'q')
	{
		switch(touche)
		{
			case KEY_DOWN:
				index += (index < filelist->nbFile-1);
				break;
			
			case KEY_UP:
				index -= (index > 0);
				break;
			
			case 10:
				fl_changePath(index);
				index = 0;
				break;
		}
		di_updateBoxing(filelist->currentPath,"Playlist");
		di_updateFilelist(0,index);
		di_refresh();
	}
	ev_end();
	
	return 0;
}

void ev_end()
{
	fl_end();
	di_end();
}
