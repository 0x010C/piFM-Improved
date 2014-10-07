#ifndef __PARAM_H
#define __PARAM_H


/*
 * Structures
 */
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
#include "main.h"


/*
 * Functions' header
 */
void pa_init();
void pa_parse(int argc, char **argv);
void pa_end();


#endif
