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
	init_pair(1, COLOR_WHITE, COLOR_BLUE); /* Fond */
	init_pair(2, COLOR_YELLOW, COLOR_BLACK); /* Sélectionné */
	init_pair(3, COLOR_GREEN, COLOR_BLUE); /* Joué */
	init_pair(4, COLOR_GREEN, COLOR_BLACK); /* Sélectionné et joué */
}

void di_refresh()
{
	refresh();
}

void di_updatePlaylist(const int firstIndex, const int selectedIndex, const int playedIndex)
{
	int index, line, j;
	
	attron(COLOR_PAIR(1));
	for(line=1,index=firstIndex;line<HEIGHT-1 && index<playlist->nbFile;line++,index++)
	{
		if(index == selectedIndex && index == playedIndex)
			attron(COLOR_PAIR(4));
		else if(index == selectedIndex)
			attron(COLOR_PAIR(2));
		else if(index == playedIndex)
			attron(COLOR_PAIR(3));

		for(j=0;j<SIZE_RIGHT-2 && j<strlen(playlist->displayList[index]);j++)
			mvprintw(line,j+SIZE_LEFT+1,"%c",playlist->displayList[index][j]);
		for(;j<SIZE_RIGHT-2;j++)
			mvprintw(line,j+SIZE_LEFT+1," ");

		if(index == selectedIndex || index == playedIndex)
			attron(COLOR_PAIR(1));
	}
	for(;line<HEIGHT-1;line++)
		for(j=0;j<SIZE_RIGHT-2;j++)
			mvprintw(line,j+SIZE_LEFT+1," ");
	attroff(COLOR_PAIR(1));
}

void di_updateFilelist(const int firstIndex, const int selectedIndex)
{
	int index, line, j;
	
	attron(COLOR_PAIR(1));
	for(line=1,index=firstIndex;line<HEIGHT-1 && index<filelist->nbFile;line++,index++)
	{
		if(index == selectedIndex)
			attron(COLOR_PAIR(2));

		for(j=0;j<SIZE_LEFT-2 && j<strlen(filelist->list[index]);j++)
			mvprintw(line,j+1,"%c",filelist->list[index][j]);
		for(;j<SIZE_LEFT-2;j++)
			mvprintw(line,j+1," ");

		if(index == selectedIndex)
			attron(COLOR_PAIR(1));
	}
	for(;line<HEIGHT-1;line++)
		for(j=0;j<SIZE_LEFT-2;j++)
			mvprintw(line,j+1," ");
	attroff(COLOR_PAIR(1));
}

void di_updateBoxing(char *title1, char *title2)
{
	/* Draw the top-line */
	int i,j;
	
	attron(COLOR_PAIR(1));
	mvprintw(0,0,"+");
	for(i=1;i<(SIZE_LEFT-strlen(title1))/2-1 && strlen(title1)+4 < SIZE_LEFT;i++)
		mvprintw(0,i,"-");
	mvprintw(0,i++,"|");
	for(j=0;i<SIZE_LEFT-2 && j<strlen(title1);j++,i++) /* TODO: Titre pas centré :'( */
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

	attroff(COLOR_PAIR(1));
}

void di_end()
{
	endwin();
}
