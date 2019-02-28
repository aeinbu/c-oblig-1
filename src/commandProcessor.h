#include <stdio.h>

#include "router.h"

#ifndef _COMMANDPROCESSOR_H
#define _COMMANDPROCESSOR_H

void executeCommands(FILE *inStream, FILE *outStream, router *routers, int *numberOfRouters);
// void executePrint(FILE *outStream, char rest[], router *routers, int *numberOfRouters);
// void executeSetFlag(FILE *outStream, char rest[], router *routers, int *numberOfRouters);
// void executeSetModel(FILE *outStream, char rest[], router *routers, int *numberOfRouters);
// void executeAddRouter(FILE *outStream, char rest[], router *routers, int *numberOfRouters);
// void executeDeleteRouter(FILE *outStream, char rest[], router *routers, int *numberOfRouters);
// void executeQueryConnectionExists(FILE *outStream, char rest[], router *routers, int *numberOfRouters);

#endif