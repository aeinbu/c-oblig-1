#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "router.h"

void loadRouters(const char filename[], router *outRouters[], size_t *outNumberOfRouters) {
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
	for(size_t i = 0; i < numberOfRouters; i++)
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


void saveRouters(const router routers[], const size_t numberOfRouters) {
	assert(routers);
	//TODO: Save router data
}


void freeRouters(router *routers[], size_t *numberOfRouters) {
	assert(routers);
	assert(numberOfRouters);

	for(size_t i = 0; i < *numberOfRouters; i++) {
		free((*routers)[i].model);
	}

	free(*routers);
	*routers = NULL;
	*numberOfRouters = 0;
}


router *findRouterById(const unsigned char routerId, router routers[], const size_t numberOfRouters) {
	assert(routers);

	for(size_t i = 0; i < numberOfRouters; i++) {
		if(routers[i].id == routerId) {
			return &routers[i];
		}
	}

	return NULL;
}


bool setFlagOnRouter(router *router, unsigned char flagNumber, unsigned char value) {
	assert(router);

    switch(flagNumber) {
        case 0:
            router->flags.active = value;
            break;
        case 1:
            router->flags.wireless = value;
            break;
        case 2:
            router->flags._5GHz = value;
            break;
        case 4:
            router->flags.changeNumber = value;
            break;
        default:
			// failed to set flag
			return false;
    }

	return true;
}


bool setModelOnRouter(router *router, char model[]) {
	assert(router);

    free(router->model);
    router->model = model;

	return true;
}


bool addRouteOnRouter(router *fromRouter, router *toRouter) {
	assert(fromRouter);
	assert(toRouter);

	if(fromRouter->numberOfConnections == MAX_NUMBER_OF_CONNECTIONS) {
		return false;
	}

	fromRouter->connections[fromRouter->numberOfConnections++] = toRouter;
	return true;
}


bool _removeConnection(router *fromRouter, router *routerToRemove) {
	for(size_t i = 0; i < fromRouter->numberOfConnections; i++) {
		if(fromRouter->connections[i] == routerToRemove) {
			fromRouter->connections[i] = fromRouter->connections[--fromRouter->numberOfConnections];
			return true;
		}
	}

	// not found, thus none removed
	return false;
}


bool deleteRouter(router *routerToDelete, router routers[], size_t *numberOfRouters) {
	assert(routerToDelete);
	assert(routers);
	assert(numberOfRouters);

	for(size_t i = 0; i < *numberOfRouters; i++)
	{
		_removeConnection(&routers[i], routerToDelete);
	}

	for(size_t i = 0; i < *numberOfRouters; i++) {
		if(&routers[i] == routerToDelete) {
			routers[i] = routers[--*numberOfRouters];
			return true;
		}
	}

	return false;	
}


bool findRouteBetweenRouters(router *fromRouter, router *toRouter, router *outRoutersFound[], size_t *outNumberOfFoundRouters) {
	assert(fromRouter);
	assert(toRouter);
	assert(outRoutersFound);
	assert(outNumberOfFoundRouters);

	//TODO: find route and return result as list of routers in outRouters and outNumberOfRouters
	//TODO: also return true when a connection was found, false when none
	return false;	//TODO:
}


