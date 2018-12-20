#include "sys.h"
#include <stdlib.h>
#include <stdio.h>

int been_here = 0;
int TEST_really_exit = 1;

void PDFatalError(char *pThe_str) {
	if (been_here) {
		exit(1);
	}
	been_here = 1;

	printf("FATAL ERROR: %s\n", pThe_str);
	// wait for keypress
	// DoSaveGame() -> exit
    if (TEST_really_exit) {
	   exit(1);
    }
}

int PDFileUnlock (char *pThe_path) {
	return 0;
}