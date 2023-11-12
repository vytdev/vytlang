#ifndef __VYTLANG_COMPILER_TOKEN_H
#define __VYTLANG_COMPILER_TOKEN_H

#include <stddef.h>

typedef enum {
	TOKEN_TYPE_OPERATOR,
	TOKEN_TYPE_IDENTIFIER,
	TOKEN_TYPE_BRACKET,
	TOKEN_TYPE_SEPARATOR,
	TOKEN_TYPE_LITERAL,
} TokenType;

typedef enum {
	TOKEN_CLASS_INT,
	// operators
	TOKEN_CLASS_DOT,         // .
	TOKEN_CLASS_COMMA,       // ,
	TOKEN_CLASS_COLON,       // :
	TOKEN_CLASS_COLON_COLON, // :
	TOKEN_CLASS_PLUS,        // +
	TOKEN_CLASS_PLUS_PLUS,   // ++
	TOKEN_CLASS_MINUS,       // -
	TOKEN_CLASS_MINUS_MINUS, // --
	TOKEN_CLASS_MINUS_GREAT, // ->
	TOKEN_CLASS_STAR,        // *
	TOKEN_CLASS_STAR_STAR,   // **
	TOKEN_CLASS_SLASH,        // /
	TOKEN_CLASS_AND,         // &
	TOKEN_CLASS_AND_AND,     // &&
	TOKEN_CLASS_OR,          // |
	TOKEN_CLASS_OR_OR,       // ||
	TOKEN_CLASS_LESS,        // <
	TOKEN_CLASS_LESS_LESS,   // <<
	TOKEN_CLASS_GREAT,       // >
	TOKEN_CLASS_GREAT_GREAT, // >>
	TOKEN_CLASS_EQUAL,       // =
	TOKEN_CLASS_EQUAL_EQUAL, // ==
	TOKEN_CLASS_LESS_EQUAL,  // <=
	TOKEN_CLASS_GREAT_EQUAL, // >=
	TOKEN_CLASS_CARET,       // ^
	TOKEN_CLASS_PERCENT,     // %
	TOKEN_CLASS_TILDE,       // ~
	TOKEN_CLASS_EXCLAMATION, // !
} TokenClass;

// a token
typedef struct {
	// tracking info
	size_t line;
	size_t col;
	size_t pos;
	// type of token
	TokenType type;
	// class of token
	TokenClass name;
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

#endif // __VYTLANG_COMPILER_TOKEN_H
