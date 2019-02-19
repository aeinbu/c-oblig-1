#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "router.h"
#include "commandProcessor.h"

int main(int argc, char *argv[]) {
	// //TODO:
	// assert(argc == 3);
	// char *routersFilename = argv[1];
	// char *commandsFilename = argv[2];
	char *routersFilename = "./data/5_routers_fully_connected";
	char *commandsFilename = "./data/kommandoer_10_routers.txt";

	router *routers;
	int numberOfRouters;
	loadRouters(routersFilename, &routers, &numberOfRouters);

	printf("Succesfully loaded information about %d routers.\n", numberOfRouters);
	// for(int i = 0; i < numberOfRouters; i++) {
	// 	printf("Id: %2hhx, Flags: %2hhx, Name: %s\n", routers[i].id, routers[i].flags, routers[i].model);
	// }



	FILE *file = fopen(commandsFilename, "r");
	assert(file);

	executeCommands(file, stdout);

	fclose(file);

	saveRouters(routers, numberOfRouters);
	freeRouters(routers, numberOfRouters);
}