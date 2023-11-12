#include "util.h"
#include "err.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

char* util_readFile(const char* path) {
	FILE* file = fopen(path, "r");
	if (!file) {
		vseterrmsg(path);
		vseterrno(vENOENT);
		return NULL;
	}

	// get file size
	fseek(file, 0, SEEK_END);
	size_t size = ftell(file);
	fseek(file, 0, SEEK_SET);

	// allocate memory for file
	char* buffer = (char*) malloc(sizeof(char) * (size + 1));
	if (!buffer) {
		vseterrno(vENOMEM);
		return NULL;
	}

	// read file and NUL-terminate it
	fread(buffer, 1, size, file);
	buffer[size] = '\0';
	fclose(file);

	// return contents
	return buffer;
}
