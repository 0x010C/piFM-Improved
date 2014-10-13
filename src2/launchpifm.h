#ifndef __LAUNCHPIFM_H
#define __LAUNCHPIFM_H


/*
 * Includes
 */
#include "main.h"


/*
 * Functions' header
 */
void lp_start();
void lp_continue();
void *lp_loop(void *notUsed);
void lp_pause();
void lp_stop();


#endif
