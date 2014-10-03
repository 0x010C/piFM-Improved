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
#include "param.h"
#include "filelist.h"
#include "playlist.h"
#include "display.h"
#include "event.h"
#include <ncurses.h>


/*
 * Macros
 */
#define MIN(a, b)	((a) < (b) ? (a) : (b))
#define MAX(a, b)	((a) > (b) ? (a) : (b))


/*
 * Variables Globales
 */
PlayList *playlist;
FileList *filelist;
Param *param;
TaskToWait *tasktowait;


#endif
