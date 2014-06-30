#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <string.h>

#include "main.h"

int ev_loop()
{
	fl_init("/");
	int firstIndex=0, selectedIndex=0;
	int touche = ' ';

	do
	{
		switch(touche)
		{
			case KEY_DOWN:
				selectedIndex += (selectedIndex < filelist->nbFile-1);
				while(selectedIndex > firstIndex+height-2-1)
					firstIndex++;
				break;
				
			case KEY_UP:
				selectedIndex -= (selectedIndex > 0);
				while(selectedIndex < firstIndex)
					firstIndex--;
				break;
				
			case KEY_STAB:
				if(param->mode == mo_file)
					param->mode = mo_play;
				else
					param->mode = mo_file;
				firstIndex = 0;
				selectedIndex = 0;
				break;
				
			case KEY_ENTER:
				if(param->mode == mo_file)
				{
					if(isDirectory(filelist->list[selectedIndex]))
					{
						fl_changePath(filelist->list[selectedIndex]);
						firstIndex = 0;
						selectedIndex = 0;
					}
				}
				//else ...
				break;
		}
		di_updateBoxing();
		di_updateFilelist(filelist, firstIndex, selectedIndex);
		di_refresh();
	} while((touche=getch()) != 'q');

	fl_end();
	return 0;
}
