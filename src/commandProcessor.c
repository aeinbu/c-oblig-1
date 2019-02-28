#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commandProcessor.h"
#include "router.h"

void executeCommands(FILE *inStream, FILE *outStream) {
    assert(inStream);
    assert(outStream);

    char inStr[300];
    while (fgets(inStr, sizeof(inStr), inStream) != NULL) {
        char *command = strtok(inStr, " ");
        char *rest = strtok(NULL, "\n");
        printf("Command: %s, rest: %s\n", command, rest);

        if (strcmp(command, "print")) {
            executePrint(outStream, rest);
            continue;
        }

        if (strcmp(command, "sett_flag")) {
            executeSet(outStream, rest);
            continue;
        }

        if (strcmp(command, "sett_model")) {
            executeSetModel(outStream, rest);
            continue;
        }

        if (strcmp(command, "legg_til")) {
            executeAddRouter(outStream, rest);
            continue;
        }

        if (strcmp(command, "slett_ruter")) {
            executeDeleteRouter(outStream, rest);
            continue;
        }

        if (strcmp(command, "finnes_rute")) {
            executeQueryConnectionExists(outStream, rest);
            continue;
        }

        break;
    };

    return;
}


void executePrint(FILE *outStream, char rest[]) {
	unsigned char routerId = 255;
	fprintf(outStream, "executePrint, rest params: %s\n", rest);
    // print <ruter-ID>
}


void executeSet(FILE *outStream, char rest[]) {
	unsigned char routerId = 255;
	fprintf(outStream, "executeSet, rest params: %s\n", rest);
    // sett <flag> <ruter-ID> <flag> <verdi>
}


void executeSetModel(FILE *outStream, char rest[]) {
	unsigned char routerId = 255;
	fprintf(outStream, "executeSetModel, rest params: %s\n", rest);
    // sett_model <ruter-ID> <navn>
}


void executeAddRouter(FILE *outStream, char rest[]) {
	unsigned char routerId = 255;
	fprintf(outStream, "executeAddRouter, rest params: %s\n", rest);
    // legg_til <kobling> <ruter-ID> <ruter-ID>
}


void executeDeleteRouter(FILE *outStream, char rest[]) {
	unsigned char routerId = 255;
	fprintf(outStream, "executeDeleteRouter, rest params: %s\n", rest);
    // slett_ruter <ruter-ID>
}


void executeQueryConnectionExists(FILE *outStream, char rest[]) {
	fprintf(outStream, "executeQueryConnectionExists, rest params: %s\n", rest);
    // finnes_rute <ruter-ID> <ruter-ID>
}
