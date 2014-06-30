#ifndef __PARAM_H
#define __PARAM_H


/*
 * Structures
 */
typedef enum Mode Mode;
enum Mode
{
	mo_file,
	mo_play
};

typedef struct Param Param;
struct Param
{
	float frequence;
	int playedIndex;
	Mode mode;
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
