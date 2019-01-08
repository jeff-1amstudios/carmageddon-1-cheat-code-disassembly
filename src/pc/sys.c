#include "sys.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

/* enable clock_gettime */
#define _POSIX_C_SOURCE 200112L

int been_here = 0;
int TEST_really_exit = 1;

unsigned long PDGetTotalTime()
{
    struct timespec spec;
    clock_gettime(CLOCK_MONOTONIC, &spec);
    return spec.tv_sec * 1000 + spec.tv_nsec / 1000;
}

void PDFatalError(char *pThe_str)
{
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

int PDFileUnlock (char *pThe_path)
{
	return 0;
}
