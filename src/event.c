#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <string.h>

#include "main.h"

int ev_loop()
{
	filelist = getFileList("/\0");
	int firstIndex=0, selectedIndex=0;
	int touche = ' ';
	char *currentPath;

	currentPath = (char*) malloc(sizeof(char)*2);
	strcpy(currentPath,"/\0");
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
					currentPath = changePath(currentPath, filelist->list[selectedIndex]);
					if(isDirectory(currentPath))
					{
						removeFileList(filelist);
						filelist = getFileList(currentPath);
						firstIndex = 0;
						selectedIndex = 0;
					}
					else
						currentPath = changePath(currentPath, "..");
				}
				//else ...
				break;
		}
		updateBoxing();
		updateFilelist(filelist, firstIndex, selectedIndex);
		refreshDisplay();
	} while((touche=getch()) != 'q');
		
	free(currentPath);
	removeFileList(filelist);
	return 0;
}
