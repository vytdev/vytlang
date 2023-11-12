#include "token.h"
#include "../err.h"
#include <stdlib.h>

void TokenList_create(TokenList* list) {
	list->data = (Token*) malloc(sizeof(Token) * 2);

	// malloc failed
	if (!list->data) {
		vseterrno(vENOMEM);
		return;
	}

	list->__buffer = 2;
	list->length = 0;
}

void TokenList_addToken(TokenList* list, Token tok) {
	// were getting no space
	if (list->__buffer <= list->length) {
		list->__buffer *= 2;
		list->data = (Token*) realloc(list->data, sizeof(Token) * list->__buffer);

		// realloc failed
		if (!list->data) {
			vseterrno(vENOMEM);
			return;
		}
	}

	// add the token
	list->data[list->length++] = tok;
}

void TokenList_destroy(TokenList* list) {
	if (list->data) {
		// free allocated memory for the text
		for (int i = 0; i < list->length; i++) {
			if (list->data[i].text) free(list->data[i].text);
		}

		// free the token list heap pointer
		free(list->data);
	}
}
