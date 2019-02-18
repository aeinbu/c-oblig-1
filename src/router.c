#include <stdlib.h>
#include <stdio.h>

#include "router.h"

router *loadRouters() {
	FILE *file = fopen("./data/5_routers_fully_connected", "r");
	if(file == 0) {
		// fopen failed
		return NULL;
	}

	int numberOfRouters;
	int intReadCount = fread(&numberOfRouters, sizeof(int), 1, file);
	if(intReadCount < 1) {
		// fread failed
		return NULL;
	}
	if(numberOfRouters == 0) {
		// no routers
		return NULL;
	}

	router *routers = calloc(numberOfRouters, sizeof(router));
	if(routers == NULL) {
		// malloc/calloc failed
		return NULL;
	}

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

		printf("Id: %2hhx, Flags: %2hhx, Name: %s\n", routers[i].id, routers[i].flags, routers[i].model);
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

//TODO: return number of routers that are read from the file, so that the size of the routers array is known
//TODO: remember to free all model names (strings) when routers is free'd

	fclose(file);

	return routers;
}
