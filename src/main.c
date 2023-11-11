#include "util.h"
#include "err.h"
#include "lexer/parser.h"
#include "lexer/token.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	if (argc != 2) {
		fprintf(stderr, "vyt: please provide file\n");
		return 1;
	}

	char* text = util_readFile(argv[1]);

	// an error happened after reading file
	if (verrno != 0) {
		vperror();
		return 1;
	}

	// create token list
	TokenList list;
	TokenList_create(&list);

	// token list not created
	if (!list.data) {
		fprintf(stderr, "vyt: failed to allocate memory\n");
		return 1;
	}

	// tokenize the source
	tokenize(text, &list);

	// an error happened during tokenization
	if (verrno != 0) {
		vperror();
		return 1;
	}

	// post cleanup
	TokenList_destroy(&list);

	return 0;
}
