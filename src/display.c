#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

#include "display.h"

void startDisplay()
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

void refreshDisplay()
{
	refresh();
}

void updatePlaylist()
{

}

void updateFilelist(FileList *filelist, int firstIndex, int selectedIndex)
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

	refresh();
}

void updateBoxing()
{
	int i=0, j=0;
	char *chaine = (char*) malloc(sizeof(char)*9);
	strcpy(chaine, "Music\0");

	attron(COLOR_PAIR(1));

	/* Haut gauche */
	//mvprintw(0,0,"+");
	move(0,0);
	addstr("┌");
	for(i=0;i<(sizeLeft-4-strlen(chaine))/2;i++)
		mvprintw(0,i+1,"%c",'o');
	mvprintw(0,(sizeLeft-4-strlen(chaine))/2+1,"|");
	mvprintw(0,(sizeLeft-4-strlen(chaine))/2+2,"%s",chaine);
	mvprintw(0,(sizeLeft-4-strlen(chaine))/2+2+strlen(chaine),"|");
	for(i=0;i<(sizeLeft-4-strlen(chaine))/2+((sizeLeft-4-strlen(chaine))%2 == 1);i++)
		mvprintw(0,i+(sizeLeft-4-strlen(chaine))/2+3+strlen(chaine),"-");
	mvprintw(0,sizeLeft-1,"+");

	/* Haut droit */
	strcpy(chaine, "Playlist\0");

	mvprintw(0,sizeLeft,"+");
	for(i=0;i<(sizeRight-4-strlen(chaine))/2;i++)
		mvprintw(0,sizeLeft+i+1,"-");
	mvprintw(0,sizeLeft+(sizeRight-4-strlen(chaine))/2+1,"|");
	mvprintw(0,sizeLeft+(sizeRight-4-strlen(chaine))/2+2,"%s",chaine);
	mvprintw(0,sizeLeft+(sizeRight-4-strlen(chaine))/2+2+strlen(chaine),"|");
	for(i=0;i<(sizeRight-4-strlen(chaine))/2+((sizeRight-4-strlen(chaine))%2 == 1);i++)
		mvprintw(0,sizeLeft+i+(sizeRight-4-strlen(chaine))/2+3+strlen(chaine),"-");
	mvprintw(0,sizeLeft+sizeRight-1,"+");

	/* Centre */
	for(i=1;i<height;i++)
	{
		mvprintw(i,0,"|");

		//for(j=0;j<sizeLeft-2;j++)
		//	mvprintw(i,j+1," ");

		mvprintw(i,sizeLeft-1,"|");
		mvprintw(i,sizeLeft,"|");

		//for(j=0;j<sizeRight-2;j++)
		//	mvprintw(i,j+sizeLeft+1," ");

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

	refresh();
	
	free(chaine);
}

void stopDisplay()
{
	endwin();
}
