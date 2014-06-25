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
void startDisplay();
void refreshDisplay();
void updatePlaylist();
void updateFilelist(FileList *filelist, int firstIndex, int selectedIndex);
void updateBoxing();
void stopDisplay();


#endif
