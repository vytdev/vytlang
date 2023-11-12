#include "err.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>

Verrcode verrno = vEMPTY;
char* verrmsg = NULL;

void vseterrno(Verrcode err) {
	verrno = err;
}

void vseterrmsg(const char* msg, ...) {
	va_list args;
	va_start(args, msg);

	// msg already set, deallocate it
	if (verrmsg) free(verrmsg);

	// get the output length
	size_t length = vsnprintf(NULL, 0, msg, args);
	// allocate memory for string
	verrmsg = (char*) malloc(length + 1);
	// format the string
	vsnprintf(verrmsg, length + 1, msg, args);

	va_end(args);
}

void vperror(void) {
	fprintf(stderr, "vyt: ");

	switch (verrno) {
		// generic
		case vEMPTY: break; // just do nothing
		case vENOMEM: fprintf(stderr, "insufficient memory"); break;
		case vENOENT: fprintf(stderr, "no such file or directory"); break;
		case vEREAD: fprintf(stderr, "read error"); break;
		// parser specific
		case vEPUCMT: fprintf(stderr, "parser: unterminated comment"); break;
	}

	// verrmsg is set
	if (verrmsg) {
		fprintf(stderr, ": %s", verrmsg);
		free(verrmsg);
	}

	fprintf(stderr, "\n");
}
