#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "router.h"

void loadRouters(char filename[], router *outRouters[], int *outNumberOfRouters) {
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
		fgetc(file);	// read past newline
		fread(&(routers[i]), sizeof(unsigned char), 2, file);

		unsigned char lengthOfName;
		fread(&lengthOfName, sizeof(unsigned char), 1, file);
		
		routers[i].model = malloc(lengthOfName);
		fgets(routers[i].model, lengthOfName, file);

		routers[i].numberOfRoutes = 0;
	}

	fgetc(file);	// read past newline

	// read routes
	while(!feof(file)) {
		unsigned char from;
		fread(&from, sizeof(unsigned char), 1, file);
		unsigned char to;
		fread(&to, sizeof(unsigned char), 1, file);

		routers[from].routes[routers[from].numberOfRoutes++] = to;

		fgetc(file);	//read past newline
	}

	fclose(file);

	*outRouters = routers;
	*outNumberOfRouters = numberOfRouters;
	return;
}


void saveRouters(router *routers, int numberOfRouters) {
	//TODO:
}


void freeRouters(router *routers, int numberOfRouters) {
	for(int i = 0; i < numberOfRouters; i++) {
		free(routers[i].model);
		routers[i].model = NULL;
	};

	free(routers);
}