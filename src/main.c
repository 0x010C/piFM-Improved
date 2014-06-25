#include <stdlib.h>
#include <stdio.h>

#include "main.h"

int main(int argc, char **argv)
{
	startDisplay();

	eventManager();
	
	stopDisplay();

	return 0;
}
