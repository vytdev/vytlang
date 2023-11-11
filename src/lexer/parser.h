#ifndef __VYTLANG_LEXER_PARSER_H
#define __VYTLANG_LEXER_PARSER_H

#include "token.h"
#include <stddef.h>

// tokenize the string and store tokens to list
void tokenize(char* text, TokenList* list);

// increment counter based on given character
void parser_increment(char ch, size_t* line, size_t* col);

#endif // __VYTLANG_LEXER_PARSER_H
