#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "commandProcessor.h"
#include "router.h"

void executeCommands(FILE *inStream, FILE *outStream) {
	assert(inStream);
	assert(outStream);

	char inStr[256];
	while(fgets(inStr, sizeof(inStr), inStream) != NULL) {
		fprintf(outStream, ">%s", inStr);
		// split string into tokens
		// switch on command, send tokenized string params
		// execute command with params

	};

	return;
}

// // Kommandoer
// print <ruter-ID>
// sett <flag> <ruter-ID> <flag> <verdi>
// sett_model <ruter-ID> <navn>
// legg_til <kobling> <ruter-ID> <ruter-ID>
// slett_ruter <ruter-ID>
// finnes_rute <ruter-ID> <ruter-ID> 