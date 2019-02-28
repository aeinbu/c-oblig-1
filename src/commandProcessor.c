#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commandProcessor.h"
#include "router.h"

void assertInteger(char str[]) {
    for(int i = 0; i < strlen(str); i++) {
        assert(isdigit(str[i]) != 0);
    }
}


void executePrint(FILE *outStream, char rest[], router *routers, int *numberOfRouters) {
    // print <ruter-ID>
    char *routerIdAsString = strtok(rest, "");
    assertInteger(routerIdAsString);
	unsigned char routerId = (unsigned char)atoi(routerIdAsString);

    router *router = findRouterById(routerId, routers, *numberOfRouters);
    printf("Router Id: %3hhu, Modell: %s\n\tActive: %d\n\tWireless: %d\n\t5GHz: %d\n\tChange number: %2d\n", router->id, router->model, router->flags.active, router->flags.wireless, router->flags._5GHz, router->flags.changeNumber);
}


void executeSetFlag(FILE *outStream, char rest[], router *routers, int *numberOfRouters) {
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
    printf("Set flags on router id: %3hhu\n", router->id);

    switch(flagNumber) {
        case 0:
            router->flags.active = value;
            break;
        case 1:
            router->flags.wireless = value;
            break;
        case 2:
            router->flags._5GHz = value;
            break;
        case 4:
            router->flags.changeNumber = value;
            break;
        default:
            assert(0);
    }
}


void executeSetModel(FILE *outStream, char rest[], router *routers, int *numberOfRouters) {
    // sett_model <ruter-ID> <navn>
    char *routerIdAsString = strtok(rest, " ");
    assertInteger(routerIdAsString);
	unsigned char routerId = (unsigned char)atoi(routerIdAsString);

    char *nameFromToken = strtok(NULL, "");
    assert(nameFromToken);
    int nameLength = strlen(nameFromToken);
    char *name = calloc(nameLength + 1, sizeof(char));
    strncpy(name, nameFromToken, nameLength);

    router *router = findRouterById(routerId, routers, *numberOfRouters);
    printf("Set model on router id: %3hhu\n", router->id);

    free(router->model);
    router->model = name;
}


void executeAddRoute(FILE *outStream, char rest[], router *routers, int *numberOfRouters) {
    // legg_til_kobling <ruter-ID> <ruter-ID>
    char *fromRouterIdAsString = strtok(rest, " ");
    assertInteger(fromRouterIdAsString);
	unsigned char fromRouterId = (unsigned char)atoi(fromRouterIdAsString);


    char *toRouterIdAsString = strtok(NULL, " ");
    assertInteger(toRouterIdAsString);
	unsigned char toRouterId = (unsigned char)atoi(toRouterIdAsString);

	fprintf(outStream, "Setup route between routers with id: %hhu and %hhu\n", fromRouterId, toRouterId);
    //TODO: Create a connection between two routers (one-way)
}


void executeDeleteRouter(FILE *outStream, char rest[], router *routers, int *numberOfRouters) {
    // slett_router <ruter-ID>
    char *routerIdAsString = strtok(rest, " ");
    assertInteger(routerIdAsString);
	unsigned char routerId = (unsigned char)atoi(routerIdAsString);

	fprintf(outStream, "Deleting router: %hhu\n", routerId);
    //TODO: delete router and connections to it...
}


void executeQueryConnectionExists(FILE *outStream, char rest[], router *routers, int *numberOfRouters) {
    // finnes_rute <ruter-ID> <ruter-ID>
    char *fromRouterIdAsString = strtok(rest, " ");
    assertInteger(fromRouterIdAsString);
	unsigned char fromRouterId = (unsigned char)atoi(fromRouterIdAsString);

    char *toRouterIdAsString = strtok(NULL, " ");
    assertInteger(toRouterIdAsString);
	unsigned char toRouterId = (unsigned char)atoi(toRouterIdAsString);

	fprintf(outStream, "Query for route between routers with id: %hhu and %hhu\n", fromRouterId, toRouterId);
    //TODO: print results (Yes or No)
}


void executeCommands(FILE *inStream, FILE *outStream, router *routers, int *numberOfRouters) {
    assert(inStream);
    assert(outStream);

    char inStr[300];
    while (fgets(inStr, sizeof(inStr), inStream) != NULL) {
        printf("\n> %s", inStr);
        char *command = strtok(inStr, " ");
        char *rest = strtok(NULL, "\n");
        // printf("Command: [%s], rest: [%s]\n", command, rest);

        if (strcmp(command, "print") == 0) {
            executePrint(outStream, rest, routers, numberOfRouters);
            continue;
        }

        if (strcmp(command, "sett_flag") == 0) {
            executeSetFlag(outStream, rest, routers, numberOfRouters);
            continue;
        }

        if (strcmp(command, "sett_modell") == 0) {
            executeSetModel(outStream, rest, routers, numberOfRouters);
            continue;
        }

        if (strcmp(command, "legg_til_kobling") == 0) {
            executeAddRoute(outStream, rest, routers, numberOfRouters);
            continue;
        }

        if (strcmp(command, "slett_router") == 0) {
            executeDeleteRouter(outStream, rest, routers, numberOfRouters);
            continue;
        }

        if (strcmp(command, "finnes_rute") == 0) {
            executeQueryConnectionExists(outStream, rest, routers, numberOfRouters);
            continue;
        }

        if(strcmp(command, "avslutt") == 0) {
            break;
        }
    };

    return;
}
