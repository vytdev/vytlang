#include "parser.h"
#include "token.h"
#include "../err.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void tokenize(char* text, TokenList* list) {

#ifdef __DEBUG
	printf("[debug] tokenize: invoked!\n");
#endif // __DEBUG

	// our tracking counters
	size_t line = 1;
	size_t col = 1;
	size_t pos = 0;
	size_t len = strlen(text);

	// lexeme
	char* lex;
	// buffer size
	size_t lexBufSize = 2;
	// current length of lex
	size_t lexLen = 0;

	// the token we'll store
	Token tok;

	while (pos < len) {
		char ch = text[pos];

		// skip whitespace
		while (isspace(ch)) {
			parser_increment(ch, &line, &col);
			ch = text[++pos];
		}

		// skip comments

		// single line comments
		if (ch == '/' && text[pos + 1] == ch) {
			// lets start after the '//'
			pos += 2;
			col += 2;
			ch = text[pos];

			// loop until we find a new line
			while (ch != '\n' && pos < len) {
				parser_increment(ch, &line, &col);
				ch = text[++pos];
			}

			// the newline is not processed because our while loop stopped
			// at before that character
			line++;
			col = 1;
			pos++;
			ch = text[pos];

			// this comment is in the end of the source text, lets end the process
			if (pos >= len) break;

			// re-iterate for next token
			continue;
		}

		// multi line comments
		if (ch == '/' && text[pos + 1] == '*') {
			// lets start after the '/*'
			pos += 2;
			col += 2;
			ch = text[pos];

			// find the end of comment
			while (ch != '*' && text[pos + 1] != '/') {
				parser_increment(ch, &line, &col);
				ch = text[++pos];

				// we got a problem, the comment is not ended
				if (pos >= len) {
					vseterrno(vEPUCMT);
					return;
				}
			}

			// increment 2 more because we have '*/' at the end of the
			// comment
			pos += 2;
			col += 2;

			// this comment is in the end of the source text, like what we
			// done for single line comments, let's end the process
			if (pos >= len) break;

			// re-iterate for next token
			continue;
		}

		// TODO: complete this part
#ifdef __DEBUG
		printf("%c: %d %d\n", ch, line, col);
#endif // __DEBUG

		parser_increment(ch, &line, &col);
		pos++;
	}

}

void parser_increment(char ch, size_t* line, size_t* col) {
	switch (ch) {
		// line feed
		case '\n':
			(*line)++;
			*col = 1;
			break;
		// carriage return
		case '\r':
			*col = 1;
			break;
		// tab
		case '\t':
			*col += 8 - (*col % 8);
			break;
		// any other characters
		default:
			(*col)++;
	}
}
