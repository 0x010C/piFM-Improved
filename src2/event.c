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
	di_updatePlaylist(0, 0, 0);
	di_updateFilelist(0,0);
	di_refresh();
}

int ev_loop()
{
	int touche = ' ';
	int index = 0, firstIndex = 0;
	char *title = NULL;

	ev_init();
	while((touche=getch()) != 'q')
	{
		switch(param->mode)
		{
			case mo_file:
				switch(touche)
				{
					case KEY_DOWN:
						index += (index < filelist->nbFile-1);
						firstIndex += (index+firstIndex > HEIGHT-3 && firstIndex+HEIGHT-2 < filelist->nbFile);
						break;
			
					case KEY_UP:
						index -= (index > 0);
						firstIndex -= (index < firstIndex);
						break;
			
					case 10:
						if(fl_changePath(index))
						{
							index = 0;
							firstIndex = 0;
						}
						break;
				}
				di_updateBoxing(filelist->currentPath,"Playlist");
				di_updatePlaylist(0, 0, 0);
				di_updateFilelist(firstIndex,index);
				di_refresh();
				break;
			
			case mo_play:
				
				break;
		}
	}
	ev_end();
	
	return 0;
}

void ev_end()
{
	fl_end();
	di_end();
}
