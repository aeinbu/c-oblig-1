#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "router.h"
#include "commandProcessor.h"

int main(int argc, char *argv[]) {
	assert(argc >= 2);
	char *routersFilename = argv[1];
	char *commandsFilename = argc == 3 ? argv[2] : NULL;

	router *routers;
	size_t numberOfRouters;
	loadRouters(routersFilename, &routers, &numberOfRouters);

	printf("Succesfully loaded information about %zu routers.\n", numberOfRouters);
	// for(size_t i = 0; i < numberOfRouters; i++) {
	// 	printf("Id: %2hhx, Active: %d, Wireless: %d, 5GHz: %d, Change number: %2d, Name: %s\n", routers[i].id, routers[i].flags.active, routers[i].flags.wireless, routers[i].flags._5GHz, routers[i].flags.changeNumber, routers[i].model);
	// }



	FILE *commandStream = commandsFilename != NULL ? fopen(commandsFilename, "r") : stdin;
	assert(commandStream);

	executeCommands(commandStream, stdout, routers, &numberOfRouters);

	if(commandStream != stdin) {
		fclose(commandStream);
	}

	saveRouters(routers, numberOfRouters);
	freeRouters(&routers, &numberOfRouters);
}