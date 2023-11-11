#include "err.h"
#include <stdio.h>
#include <stdlib.h>

Verrcode verrno = vEMPTY;

void vseterrno(Verrcode err) {
	verrno = err;
}

void vperror(void) {
	switch (verrno) {
		// generic
		case vEMPTY: break; // just do nothing
		case vENOMEM: fprintf(stderr, "vyt: insufficient memory\n"); break;
		case vENOENT: fprintf(stderr, "vyt: no such file or directory\n"); break;
		// parser specific
		case vEPUCMT: fprintf(stderr, "vyt: parser: unterminated comment\n"); break;
	}
}
