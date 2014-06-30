#include <stdlib.h>
#include <stdio.h>

#include "main.h"

int main(int argc, char **argv)
{
	pa_init();
	pa_parse(argc, argv);
	
	di_init();
	fl_init();
	pl_init();

	ev_loop();
	
	pl_end();
	fl_end();
	di_end();
	pa_end();

	return 0;
}
