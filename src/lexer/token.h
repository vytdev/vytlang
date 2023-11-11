#ifndef __VYTLANG_LEXER_TOKEN_H
#define __VYTLANG_LEXER_TOKEN_H

#include <stddef.h>

typedef enum {
	TOKEN_TYPE_OPERATOR,
	TOKEN_TYPE_IDENTIFIER,
	TOKEN_TYPE_BRACKET,
	TOKEN_TYPE_SEPARATOR,
	TOKEN_TYPE_LITERAL,
} TokenType;

// a token
typedef struct {
	// tracking info
	size_t line;
	size_t col;
	size_t pos;
	// type of token
	TokenType type;
	// the token text
	char* text;
} Token;

// a token list
typedef struct {
	// the content of list
	Token* data;
	// buffer size of list (powers of 2)
	size_t __buffer;
	// the number of items stored in our list
	size_t length;
} TokenList;

// construct a token list
void TokenList_create(TokenList* list);

// add a token to list
void TokenList_addToken(TokenList* list, Token tok);

// destroy token list
void TokenList_destroy(TokenList* list);

#endif // __VYTLANG_LEXER_TOKEN_H
