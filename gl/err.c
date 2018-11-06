#include "err.h"
#include <stdio.h>
#include "point.h"

void err_output(const char *message)
{
	fprintf(stderr, message);
	fflush(stderr);
}

void err_enable_logging(const char* logpath)
{
	err_output("logging not yet implemented");
}

void err_clear()
{
}
