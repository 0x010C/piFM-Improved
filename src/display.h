#ifndef __DISPLAY_H
#define __DISPLAY_H

/*
 * Includes
 */
#include "main.h"


/*
 * Defines
 */
#define sizeLeft getmaxx(stdscr)/2
#define sizeRight getmaxx(stdscr)/2+(getmaxx(stdscr)%2==1)
#define height getmaxy(stdscr)


/*
 * Functions' header
 */
void di_init();
void di_refresh();
void di_updatePlayList(int firstIndex, int selectedIndex);
void di_updateFileList(int firstIndex, int selectedIndex);
void di_updateBoxing();
void di_end();


#endif
