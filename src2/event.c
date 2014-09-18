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
	
	di_updateBoxing("Dossier machin/truc/bidule","Playlist");
	di_refresh();
	ev_break();
}

int ev_loop()
{
	ev_init();
	/* ... */
	ev_end();
	return 0;
}

void ev_end()
{
	di_end();
}
