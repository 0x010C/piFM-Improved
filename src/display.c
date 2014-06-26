#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <string.h>

#include "display.h"

void di_init()
{
	/*Initialisation de ncurses*/
	initscr();
	noecho();
	keypad(stdscr,TRUE);
	curs_set(0);
	start_color();

	/*Mise en place des paires de couleurs*/
	init_pair(1, COLOR_WHITE, COLOR_CYAN); /*1*/
	init_pair(2, COLOR_WHITE, COLOR_BLACK); /*2*/
}

void di_refresh()
{
	refresh();
}

void di_updatePlaylist(int firstIndex, int selectedIndex, int playedIndex)
{

}

void di_updateFilelist(int firstIndex, int selectedIndex)
{
	int i, j;

	attron(COLOR_PAIR(1));
	for(i=0;i<height-2;i++)
	{
		if(filelist->nbFile > i+firstIndex)
		{
			if(selectedIndex == i+firstIndex)
				attron(COLOR_PAIR(2));
			for(j=0;j<min(strlen(filelist->list[i+firstIndex]),sizeLeft-2);j++)
				mvprintw(i+1,j+1,"%c",filelist->list[i+firstIndex][j]);
			for(;j<sizeLeft-2;j++)
				mvprintw(i+1,j+1," ");
			if(selectedIndex == i+firstIndex)
				attron(COLOR_PAIR(1));
		}
		else
		{
			for(j=0;j<sizeLeft-2;j++)
				mvprintw(i+1,j+1," ");
		}
	}
	attroff(COLOR_PAIR(1));

	di_refresh();
}

void di_updateBoxing(char *title1, char *title2)
{
	int i=0;

	attron(COLOR_PAIR(1));

	/* Haut gauche */
	mvprintw(0,0,"+");
	for(i=0;i<(sizeLeft-4-strlen(title1))/2;i++)
		mvprintw(0,i+1,"-");
	mvprintw(0,(sizeLeft-4-strlen(title1))/2+1,"|");
	mvprintw(0,(sizeLeft-4-strlen(title1))/2+2,"%s",title1);
	mvprintw(0,(sizeLeft-4-strlen(title1))/2+2+strlen(title1),"|");
	for(i=0;i<(sizeLeft-4-strlen(title1))/2+((sizeLeft-4-strlen(title1))%2 == 1);i++)
		mvprintw(0,i+(sizeLeft-4-strlen(title1))/2+3+strlen(title1),"-");
	mvprintw(0,sizeLeft-1,"+");

	/* Haut droit */
	mvprintw(0,sizeLeft,"+");
	for(i=0;i<(sizeRight-4-strlen(title2))/2;i++)
		mvprintw(0,sizeLeft+i+1,"-");
	mvprintw(0,sizeLeft+(sizeRight-4-strlen(title2))/2+1,"|");
	mvprintw(0,sizeLeft+(sizeRight-4-strlen(title2))/2+2,"%s",title2);
	mvprintw(0,sizeLeft+(sizeRight-4-strlen(title2))/2+2+strlen(title2),"|");
	for(i=0;i<(sizeRight-4-strlen(title2))/2+((sizeRight-4-strlen(title2))%2 == 1);i++)
		mvprintw(0,sizeLeft+i+(sizeRight-4-strlen(title2))/2+3+strlen(title2),"-");
	mvprintw(0,sizeLeft+sizeRight-1,"+");

	/* Centre */
	for(i=1;i<height;i++)
	{
		mvprintw(i,0,"|");

		mvprintw(i,sizeLeft-1,"|");
		mvprintw(i,sizeLeft,"|");

		mvprintw(i,sizeLeft+sizeRight-1,"|");
	}

	/* Bas */
	mvprintw(height-1,0,"+");
	for(i=0;i<sizeLeft-2;i++)
		mvprintw(height-1,i+1,"-");
	mvprintw(height-1,sizeLeft-1,"+");
	mvprintw(height-1,sizeLeft,"+");
	for(i=0;i<sizeRight-2;i++)
		mvprintw(height-1,i+sizeLeft+1,"-");
	mvprintw(height-1,sizeLeft+sizeRight-1,"+");

	attroff(COLOR_PAIR(1));

	di_refresh();
}

void di_end()
{
	endwin();
}
