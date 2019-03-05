#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commandProcessor.h"
#include "router.h"

void assertInteger(char str[]) {
    for(size_t i = 0; i < strlen(str); i++) {
        assert(isdigit(str[i]) != 0);
    }
}


void _executePrint(FILE *outStream, char rest[], router routers[], size_t *numberOfRouters) {
    // print <ruter-ID>
    char *routerIdAsString = strtok(rest, "");
    assertInteger(routerIdAsString);
	unsigned char routerId = (unsigned char)atoi(routerIdAsString);

    router *router = findRouterById(routerId, routers, *numberOfRouters);
    fprintf(outStream, "Router Id: %3hhu, Modell: %s\n\tActive: %d\n\tWireless: %d\n\t5GHz: %d\n\tChange number: %2d\n", router->id, router->model, router->flags.active, router->flags.wireless, router->flags._5GHz, router->flags.changeNumber);
    fprintf(outStream, "SUCCESS");
}


void _executePrintAll(FILE *outStream, char rest[], router routers[], size_t *numberOfRouters) {
    // print_alle
	for(size_t i = 0; i < *numberOfRouters; i++) {
		fprintf(outStream, "Id: %2hhx, Active: %d, Wireless: %d, 5GHz: %d, Change number: %2d, Name: %s\n", routers[i].id, routers[i].flags.active, routers[i].flags.wireless, routers[i].flags._5GHz, routers[i].flags.changeNumber, routers[i].model);
	}
}


void _executeSetFlag(FILE *outStream, char rest[], router routers[], size_t *numberOfRouters) {
    // sett_flag <ruter-ID> <flag> <verdi>
    char *routerIdAsString = strtok(rest, " ");
    assertInteger(routerIdAsString);
	unsigned char routerId = (unsigned char)atoi(routerIdAsString);

    char *flagAsString = strtok(NULL, " ");
    assertInteger(flagAsString);
	unsigned char flagNumber = (unsigned char)atoi(flagAsString);

    char *valueAsString = strtok(NULL, "");
    assertInteger(valueAsString);
	unsigned char value = (unsigned char)atoi(valueAsString);

    router *router = findRouterById(routerId, routers, *numberOfRouters);
    assert(router);
    if(setFlagOnRouter(router, flagNumber, value))
    {
        fprintf(outStream, "SUCCESS: ");
    } else {
        fprintf(outStream, "FAIL: ");
    }
    fprintf(outStream, "Set/reset flag#%hhu on router id: %3hhu\n", flagNumber, router->id);
}


void _executeSetModel(FILE *outStream, char rest[], router routers[], size_t *numberOfRouters) {
    // sett_model <ruter-ID> <navn>
    char *routerIdAsString = strtok(rest, " ");
    assertInteger(routerIdAsString);
	unsigned char routerId = (unsigned char)atoi(routerIdAsString);

    char *modelFromToken = strtok(NULL, "");
    assert(modelFromToken);
    char *model = strdup(modelFromToken);

    router *router = findRouterById(routerId, routers, *numberOfRouters);
    assert(router);
    if(setModelOnRouter(router, model))
    {
        fprintf(outStream, "SUCCESS: ");
    } else {
        fprintf(outStream, "FAIL: ");
    }
    fprintf(outStream, "Set model on router id: %3hhu\n", router->id);
}


void _executeAddRoute(FILE *outStream, char rest[], router routers[], size_t *numberOfRouters) {
    // legg_til_kobling <ruter-ID> <ruter-ID>
    char *fromRouterIdAsString = strtok(rest, " ");
    assertInteger(fromRouterIdAsString);
	unsigned char fromRouterId = (unsigned char)atoi(fromRouterIdAsString);

    char *toRouterIdAsString = strtok(NULL, " ");
    assertInteger(toRouterIdAsString);
	unsigned char toRouterId = (unsigned char)atoi(toRouterIdAsString);

    router *fromRouter = findRouterById(fromRouterId, routers, *numberOfRouters);
    assert(fromRouter);
    router *toRouter = findRouterById(toRouterId, routers, *numberOfRouters);
    assert(toRouter);
    if(addRouteOnRouter(fromRouter, toRouter))
    {
        fprintf(outStream, "SUCCESS: ");
    } else {
        fprintf(outStream, "FAIL: ");
    }
	fprintf(outStream, "Setup route between routers with id: %hhu and %hhu\n", fromRouter->id, toRouter->id);
}


void _executeDeleteRouter(FILE *outStream, char rest[], router routers[], size_t *numberOfRouters) {
    // slett_router <ruter-ID>
    char *routerIdAsString = strtok(rest, " ");
    assertInteger(routerIdAsString);
	unsigned char routerId = (unsigned char)atoi(routerIdAsString);

    router *router = findRouterById(routerId, routers, *numberOfRouters);
    assert(router);
    if(deleteRouter(router, routers, numberOfRouters))
    {
        fprintf(outStream, "SUCCESS: ");
    } else {
        fprintf(outStream, "FAIL: ");
    }
	fprintf(outStream, "Delete router id: %hhu\n", routerId);
}


void _executeQueryConnectionExists(FILE *outStream, char rest[], router routers[], size_t *numberOfRouters) {
    // finnes_rute <ruter-ID> <ruter-ID>
    char *fromRouterIdAsString = strtok(rest, " ");
    assertInteger(fromRouterIdAsString);
	unsigned char fromRouterId = (unsigned char)atoi(fromRouterIdAsString);

    char *toRouterIdAsString = strtok(NULL, " ");
    assertInteger(toRouterIdAsString);
	unsigned char toRouterId = (unsigned char)atoi(toRouterIdAsString);

    router *fromRouter = findRouterById(fromRouterId, routers, *numberOfRouters);
    assert(fromRouter);
    router *toRouter = findRouterById(toRouterId, routers, *numberOfRouters);
    assert(toRouter);
    // router *routersFound;
    // size_t numberOfRoutersFound;
    if(findRouteBetweenRouters(fromRouter, toRouter, *numberOfRouters /*, &routersFound, &numberOfRoutersFound*/))
    {
        fprintf(outStream, "SUCCESS: ");
    } else {
        fprintf(outStream, "FAIL: ");
    }
	fprintf(outStream, "Find for route between routers with id: %hhu and %hhu\n", fromRouterId, toRouterId);
}


void executeCommands(FILE *inStream, FILE *outStream, router routers[], size_t *numberOfRouters) {
    assert(inStream);
    assert(outStream);

    char inStr[300];
    while (fgets(inStr, sizeof(inStr), inStream) != NULL) {
        printf("\n> %s", inStr);
        char *command = strtok(inStr, " ");
        char *rest = strtok(NULL, "\n");
        // printf("Command: [%s], rest: [%s]\n", command, rest);

        if (strcmp(command, "print") == 0) {
            _executePrint(outStream, rest, routers, numberOfRouters);
            continue;
        }

        if (strcmp(command, "print_alle") == 0) {
            _executePrintAll(outStream, rest, routers, numberOfRouters);
            continue;
        }

        if (strcmp(command, "sett_flag") == 0) {
            _executeSetFlag(outStream, rest, routers, numberOfRouters);
            continue;
        }

        if (strcmp(command, "sett_modell") == 0) {
            _executeSetModel(outStream, rest, routers, numberOfRouters);
            continue;
        }

        if (strcmp(command, "legg_til_kobling") == 0) {
            _executeAddRoute(outStream, rest, routers, numberOfRouters);
            continue;
        }

        if (strcmp(command, "slett_router") == 0) {
            _executeDeleteRouter(outStream, rest, routers, numberOfRouters);
            continue;
        }

        if (strcmp(command, "finnes_rute") == 0) {
            _executeQueryConnectionExists(outStream, rest, routers, numberOfRouters);
            continue;
        }

        if(strcmp(command, "avslutt") == 0) {
            break;
        }
    };

    return;
}
