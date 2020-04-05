#include <stdio.h>
#include <stdlib.h>

#include "sys/sys.h"

int main(int argc, char* argv[]) 
{
	if (argv[1] == NULL)
	{
		printf("[Error]: You must provide the path to a ROM file\n");
		exit(1);
	}

	// Initialize the system
	System* system = sys_create(argv[1]);
	sys_boot(system);

	// Cleanup
	sys_destroy(system);

	return 0;
}
