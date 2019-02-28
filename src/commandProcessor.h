#include <stdio.h>

#ifndef _COMMANDPROCESSOR_H
#define _COMMANDPROCESSOR_H

void executeCommands(FILE *inStream, FILE *outStream);
void executePrint(FILE *outStream, char rest[]);
void executeSet(FILE *outStream, char rest[]);
void executeSetModel(FILE *outStream, char rest[]);
void executeAddRouter(FILE *outStream, char rest[]);
void executeDeleteRouter(FILE *outStream, char rest[]);
void executeQueryConnectionExists(FILE *outStream, char rest[]);

#endif