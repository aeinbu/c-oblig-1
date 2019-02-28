#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "router.h"
#include "commandProcessor.h"



int main(int argc, char *argv[]) {
	assert(argc == 3);
	char *routersFilename = argv[1];
	char *commandsFilename = argv[2];
	// char *routersFilename = "./data/10_routers_10_edges";
	// char *commandsFilename = "./data/kommandoer_10_routers.txt";

	router *routers;
	int numberOfRouters;
	loadRouters(routersFilename, &routers, &numberOfRouters);

	printf("Succesfully loaded information about %d routers.\n", numberOfRouters);
	for(int i = 0; i < numberOfRouters; i++) {
		printf("Id: %2hhx, Active: %d, Wireless: %d, 5GHz: %d, Change number: %2d, Name: %s\n", routers[i].id, routers[i].flags.active, routers[i].flags.wireless, routers[i].flags._5GHz, routers[i].flags.changeNumber, routers[i].model);
	}



	FILE *file = fopen(commandsFilename, "r");
	assert(file);

	executeCommands(file, stdout, routers, &numberOfRouters);

	fclose(file);

	saveRouters(routers, numberOfRouters);
	freeRouters(&routers, &numberOfRouters);
}