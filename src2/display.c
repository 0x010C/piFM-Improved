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
	init_pair(2, COLOR_YELLOW, COLOR_BLACK); /*2*/
	init_pair(3, COLOR_GREEN, COLOR_CYAN); /*3*/
}

void di_refresh()
{
	refresh();
}

void di_updatePlaylist(int firstIndex, int selectedIndex, int playedIndex)
{
	
}

void di_updateFilelist(const int firstIndex, const int selectedIndex)
{
	int index, line, j;
	for(line=1,index=firstIndex;line<HEIGHT-1 && index<filelist->nbFile;line++,index++)
	{
		for(j=0;j<SIZE_LEFT && j<strlen(filelist->list[index]);j++)
			mvprintw(line,j+1,"%c",filelist->list[index][j]);
	}
}

void di_updateBoxing(char *title1, char *title2)
{
	/* Draw the top-line */
	int i,j;
	mvprintw(0,0,"+");
	for(i=1;i<(SIZE_LEFT-strlen(title1))/2-1 && strlen(title1)+4 < SIZE_LEFT;i++)
		mvprintw(0,i,"-");
	mvprintw(0,i++,"|");
	for(j=0;i<SIZE_LEFT-2 && j<strlen(title1);j++,i++)
		mvprintw(0,i,"%c",title1[j]);
	mvprintw(0,i++,"|");
	for(;i<SIZE_LEFT-1;i++)
		mvprintw(0,i,"-");
	mvprintw(0,i++,"+");
	
	mvprintw(0,i++,"+");
	for(;i<SIZE_LEFT+(SIZE_RIGHT-strlen(title2))/2-1 && strlen(title2)+4 < SIZE_RIGHT;i++)
		mvprintw(0,i,"-");
	mvprintw(0,i++,"|");
	for(j=0;i<SIZE_LEFT+SIZE_RIGHT-2 && j<strlen(title2);j++,i++)
		mvprintw(0,i,"%c",title2[j]);
	mvprintw(0,i++,"|");
	for(;i<SIZE_LEFT+SIZE_RIGHT-1;i++)
		mvprintw(0,i,"-");
		
	mvprintw(0,i++,"+");
	
	/* Draw the vertical-lines */
	for(j=1;j<HEIGHT;j++)
	{
		mvprintw(j,0,"|");
		mvprintw(j,SIZE_LEFT-1,"|");
		mvprintw(j,SIZE_LEFT,"|");
		mvprintw(j,SIZE_LEFT+SIZE_RIGHT-1,"|");
	}
	
	/* Draw the bottom-line */
	mvprintw(HEIGHT-1,0,"+");
	for(i=1;i<SIZE_LEFT-1;i++)
		mvprintw(HEIGHT-1,i,"-");
	mvprintw(HEIGHT-1,SIZE_LEFT-1,"+");
	
	mvprintw(HEIGHT-1,SIZE_LEFT,"+");
	for(i=SIZE_LEFT+1;i<SIZE_LEFT+SIZE_RIGHT-1;i++)
		mvprintw(HEIGHT-1,i,"-");
	mvprintw(HEIGHT-1,SIZE_LEFT+SIZE_RIGHT-1,"+");
}

void di_end()
{
	endwin();
}
