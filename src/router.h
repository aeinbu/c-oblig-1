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

void loadRouters(const char filename[], router *outRouters[], int *outNumberOfRouters);

void saveRouters(const router *routers, const int numberOfRouters);

void freeRouters(router *routers, const int numberOfRouters);

router *findRouterById(const unsigned char routerId, router *routers, const int numberOfRouters);

#endif