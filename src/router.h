#ifndef _ROUTER_H
#define _ROUTER_H

typedef struct {
	unsigned char id;
	unsigned char flags;
	char *model;
} router;

router *loadRouters();

#endif