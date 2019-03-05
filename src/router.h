#include <stdbool.h>

#ifndef _ROUTER_H
#define _ROUTER_H

#define MAX_NUMBER_OF_CONNECTIONS 10

typedef struct {
	unsigned char active : 1;
	unsigned char wireless : 1;
	unsigned char _5GHz : 1;
	unsigned char : 1;
	unsigned char changeNumber : 4;
} flags;

typedef struct router {
	unsigned char id;
	flags flags;
	char *model;
	int numberOfConnections;
	struct router *connections[MAX_NUMBER_OF_CONNECTIONS];
} router;

void loadRouters(const char filename[], router *outRouters[], size_t *outNumberOfRouters);

void saveRouters(const router routers[], const size_t numberOfRouters);

void freeRouters(router *routers[], size_t *numberOfRouters);

router *findRouterById(const unsigned char routerId, router routers[], const size_t numberOfRouters);

bool setFlagOnRouter(router *router, unsigned char flagNumber, unsigned char value);

bool setModelOnRouter(router *router, char model[]);

bool addRouteOnRouter(router *fromRouter, router *toRouter);

bool deleteRouter(router *routerToDelete, router routers[], size_t *numberOfRouters);

bool findRouteBetweenRouters(router *fromRouter, router *toRouter, size_t numberOfRouters/*, router *outRoutersFound[], size_t *outNumberOfFoundRouters*/);

#endif