#ifndef __DISPLAY_H
#define __DISPLAY_H

/*
 * Includes
 */
#include "main.h"


/*
 * Defines
 */
#define SIZE_LEFT getmaxx(stdscr)/2
#define SIZE_RIGHT getmaxx(stdscr)/2+(getmaxx(stdscr)%2==1)
#define HEIGHT getmaxy(stdscr)


/*
 * Functions' header
 */
void di_init();
void di_refresh();
void di_updatePlaylist(const int firstIndex, const int selectedIndex, const int playedIndex);
void di_updateFilelist(const int firstIndex, const int selectedIndex);
void di_updateBoxing(char *title1, char *title2);
void di_end();


#endif
