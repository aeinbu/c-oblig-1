#include <stdlib.h>
#include <stdio.h>

#include "router.h"

router *loadRouters() {
	FILE *file = fopen("./data/5_routers_fully_connected", "r");
	if(file == 0) {
		return NULL;
	}
	//TODO: check if file returned NULL or 0

	int numberOfRouters;
	fread(&numberOfRouters, sizeof(int), 1, file);
	router *routers = calloc(numberOfRouters, sizeof(router));
	printf("Number of routers: %d\n", numberOfRouters);


	for(int i = 0; i < numberOfRouters; i++)
	{
		fgetc(file);	// read past newline

		fread(&(routers[i]), sizeof(unsigned char), 2, file);

		unsigned char lengthOfName;
		fread(&lengthOfName, sizeof(unsigned char), 1, file);
		
		routers[i].model = malloc(lengthOfName);
		fgets(routers[i].model, lengthOfName, file);

		printf("Id: %2hhx, Flags: %2hhx, Name: %s\n", routers[i].id, routers[i].flags, routers[i].model);
	}	

	fclose(file);

	return routers;
}
