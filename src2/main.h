#ifndef __MAIN_H
#define __MAIN_H

/*
 * Structures
 */
enum Bool
{
	False = 0,
	True = 1
};
typedef enum Bool Bool;

enum Mode
{
	mo_file = 0,
	mo_play = 1
};
typedef enum Mode Mode;

typedef struct Param Param;
struct Param
{
	int frequence;
	int playedIndex;
	Mode mode;
	Bool sigEnd;
};


/*
 * Includes
 */
#include "param.h"
#include "filelist.h"
#include "playlist.h"
#include "display.h"
#include "conversion.h"
#include "event.h"
#include <ncurses.h>
#include <pthread.h>


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
pthread_t *coThread;


#endif
