#include "util.h"
#include "err.h"
#include "config.h"
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

char* util_readStdIn(void) {
	size_t size = 0;
	size_t capacity = BUFFER_SIZE;
	char* buffer = (char*) malloc(capacity);

	if (!buffer) {
		vseterrno(vENOMEM);
		return NULL;
	}

	while (1) {
		size_t bytesIn = fread(buffer + size, 1, capacity - size, stdin);

		// read failed
		if (bytesIn == 0) {
			if (feof(stdin)) break;
			vseterrno(vEREAD);
			vseterrmsg("error reading from stdin");
			free(buffer);
			return NULL;
		}

		size += bytesIn;

		// update buffer
		if (size >= capacity - 1) {
			capacity *= 2;
			char* tmp = (char*) realloc(buffer, capacity);

			// realloc failed
			if (!tmp) {
				free(buffer);
				vseterrno(vENOMEM);
				return NULL;
			}

			buffer = tmp;
		}

	}

	buffer[size] = '\0';
	return buffer;
}
