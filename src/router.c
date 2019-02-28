#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "router.h"

void loadRouters(const char filename[], router *outRouters[], int *outNumberOfRouters) {
	assert(outRouters);
	assert(outNumberOfRouters);

	FILE *file = fopen(filename, "r");
	assert(file);
	
	int numberOfRouters;
	int intReadCount = fread(&numberOfRouters, sizeof(int), 1, file);
	assert(intReadCount);
	if(numberOfRouters == 0) {
		// no routers
		*outRouters = NULL;
		*outNumberOfRouters = 0;
		return;
	}

	router *routers = calloc(numberOfRouters, sizeof(router));
	assert(routers);

	// read routers
	for(int i = 0; i < numberOfRouters; i++)
	{
		fseek(file, sizeof(char), SEEK_CUR); // read past newline
		fread(&(routers[i]), sizeof(unsigned char), 2, file);

		unsigned char lengthOfName;
		fread(&lengthOfName, sizeof(unsigned char), 1, file);
		
		routers[i].model = calloc(lengthOfName, sizeof(char));
		fgets(routers[i].model, lengthOfName, file);

		routers[i].numberOfConnections = 0;
	}

	fseek(file, sizeof(char), SEEK_CUR); // read past newline

	// read routes
	while(true) {
		unsigned char fromId;
		if(fread(&fromId, sizeof(unsigned char), 1, file)){
			break;
		};
		unsigned char toId;
		fread(&toId, sizeof(unsigned char), 1, file);

		router *fromRouter = findRouterById(fromId, routers, numberOfRouters);
		assert(fromRouter);
		assert(fromRouter->numberOfConnections < MAX_NUMBER_OF_CONNECTIONS - 1);
		router *toRouter = findRouterById(toId, routers, numberOfRouters);
		assert(toRouter);
		fromRouter->connections[fromRouter->numberOfConnections++] = toRouter;

		fseek(file, sizeof(char), SEEK_CUR); // read past newline
	}

	fclose(file);

	*outRouters = routers;
	*outNumberOfRouters = numberOfRouters;
	return;
}


void saveRouters(const router *routers, const int numberOfRouters) {
	//TODO:
}


void freeRouters(router *routers[], int *numberOfRouters) {
	for(int i = 0; i < *numberOfRouters; i++) {
		free((*routers)[i].model);
	}

	free(*routers);
	*routers = NULL;
	*numberOfRouters = 0;
}


router *findRouterById(const unsigned char routerId, router *routers, const int numberOfRouters) {
	for(int i = 0; i < numberOfRouters; i++) {
		if(routers[i].id == routerId) {
			return &routers[i];
		}
	}

	return NULL;
}