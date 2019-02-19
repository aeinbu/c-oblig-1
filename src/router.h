#ifndef _ROUTER_H
#define _ROUTER_H

typedef struct {
	unsigned char id;
	unsigned char flags;
	char *model;
	int numberOfRoutes;
	unsigned char routes[10];
} router;

void loadRouters(char filename[], router *outRouters[], int *outNumberOfRouters);

void saveRouters(router *routers, int numberOfRouters);

void freeRouters(router *routers, int numberOfRouters);

#endif