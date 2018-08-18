#include "fileRead.h"
#include <stdio.h>
#include <stdlib.h>

char *readFile(const char *path)
{
	char *buffer = NULL;
	int str_size, read_size;
	FILE *handler = fopen(path, "r");

	if(handler)
	{
		fseek(handler, 0, SEEK_END);
		str_size = ftell(handler);
		rewind(handler);
		 
		// Allocating enough memory for the file and a null end char
		buffer = malloc(sizeof(char) *  (str_size + 1));
		read_size = fread(buffer, sizeof(char), str_size, handler);

		// capping off the string
		buffer[str_size] = '\0';

		if(str_size != read_size){
			free(buffer);
			buffer = NULL;
		}
	}

	return buffer;
}
