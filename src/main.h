#ifndef __MAIN_H
#define __MAIN_H

/*
 * Structures
 */
typedef enum Bool Bool;
enum Bool
{
	False = 0,
	True = 1
};


/*
 * Includes
 */
#include "filelist.h"
#include "playlist.h"
#include "display.h"
#include "event.h"


/*
 * Macros
 */
#define min(a, b)	((a) < (b) ? (a) : (b))


/*
 * Variables Globales
 */
PlayList *playlist;
FileList *filelist;
Params *params;



#endif
