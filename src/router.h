#ifndef _ROUTER_H
#define _ROUTER_H

typedef struct {
	unsigned char id;
	unsigned char flags;
	char *model;
	int numberOfRoutes;
	unsigned char routes[10];
} router;

router *loadRouters();

#endif