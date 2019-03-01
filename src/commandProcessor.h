#include <stdbool.h>
#include <stdio.h>

#include "router.h"

#ifndef _COMMANDPROCESSOR_H
#define _COMMANDPROCESSOR_H

void executeCommands(FILE *inStream, FILE *outStream, router routers[], size_t *numberOfRouters);

#endif