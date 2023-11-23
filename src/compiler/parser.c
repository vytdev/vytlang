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

			// this comment is in the end of the source text, and like what we
			// done for single line comments, let's end the process
			if (pos >= len) break;

			// re-iterate for next token
			continue;
		}

		// a possible identifier or keyword
		if (isalpha(ch)) {
			Token tok;
			tok.line = line;
			tok.col = col;
			tok.pos = pos;
			tok.type = TOKEN_TYPE_IDENTIFIER;
			tok.name = TOKEN_CLASS_IDENTIFIER;

			char* lex = (char*) malloc(sizeof(char) * 2);

			// malloc failed
			if (!lex) {
				vseterrno(vENOMEM);
				return;
			}

			size_t bufferSize = 2;
			size_t idx = 0;

			while (isalpha(text[pos]) || isdigit(text[pos])) {
				if (bufferSize <= idx) {
					bufferSize *= 2;
					char* tmp = (char*) realloc(lex, sizeof(char*) * bufferSize);

					// out of memory upon realloc
					if (!tmp) {
						free(lex);
						vseterrno(vENOMEM);
						return;
					}

					lex = tmp;
				}

				lex[idx++] = text[pos++];
				parser_increment(text[pos - 1], &line, &col);

				// were on the end
				if (pos >= len) break;
			}

			// nul-terminate the string
			lex[idx] = '\0';
			// set the text
			tok.text = lex;

			// check for keyword
			bool isKwd = false;
			if      (strcmp(lex, "if") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KIF; }
			else if (strcmp(lex, "else") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KELSE; }
			else if (strcmp(lex, "try") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KTRY; }
			else if (strcmp(lex, "catch") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KCATCH; }
			else if (strcmp(lex, "finally") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KFINALLY; }
			else if (strcmp(lex, "switch") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KSWITCH; }
			else if (strcmp(lex, "case") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KCASE; }
			else if (strcmp(lex, "with") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KWITH; }
			else if (strcmp(lex, "do") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KDO; }
			else if (strcmp(lex, "while") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KWHILE; }
			else if (strcmp(lex, "for") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KFOR; }
			else if (strcmp(lex, "break") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KBREAK; }
			else if (strcmp(lex, "continue") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KCONTINUE; }
			else if (strcmp(lex, "delete") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KDELETE; }
			else if (strcmp(lex, "new") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KNEW; }
			else if (strcmp(lex, "using") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KUSING; }
			else if (strcmp(lex, "import") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KIMPORT; }
			else if (strcmp(lex, "export") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KEXPORT; }
			else if (strcmp(lex, "expose") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KEXPOSE; }
			else if (strcmp(lex, "var") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KVAR; }
			else if (strcmp(lex, "namespace") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KNAMESPACE; }
			else if (strcmp(lex, "function") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KFUNCTION; }
			else if (strcmp(lex, "throw") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KTHROW; }
			else if (strcmp(lex, "return") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KRETURN; }
			else if (strcmp(lex, "class") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KCLASS; }
			else if (strcmp(lex, "extends") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KEXTENDS; }
			else if (strcmp(lex, "implements") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KIMPLEMENTS; }
			else if (strcmp(lex, "public") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KPUBLIC; }
			else if (strcmp(lex, "private") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KPRIVATE; }
			else if (strcmp(lex, "protected") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KPROTECTED; }
			else if (strcmp(lex, "static") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KSTATIC; }
			else if (strcmp(lex, "dynamic") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KDYNAMIC; }
			else if (strcmp(lex, "abstract") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KABSTRACT; }
			else if (strcmp(lex, "override") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KOVERRIDE; }
			else if (strcmp(lex, "enum") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KENUM; }
			else if (strcmp(lex, "interface") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KINTERFACE; }
			else if (strcmp(lex, "type") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KTYPE; }
			else if (strcmp(lex, "keyof") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KKEYOF; }
			else if (strcmp(lex, "const") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KCONST; }
			else if (strcmp(lex, "template") == 0) { isKwd = true; tok.name = TOKEN_CLASS_KTEMPLATE; }
			if (isKwd) tok.type = TOKEN_TYPE_KEYWORD;

			// add this token
			TokenList_addToken(list, tok);
			// problem adding token
			if (verrno != 0) return;

			// re-iterate for next token
			continue;
		}

		// numbers
		if (isdigit(ch)) {
			Token tok;
			tok.line = line;
			tok.col = col;
			tok.pos = pos;
			tok.type = TOKEN_TYPE_LITERAL;
			tok.name = TOKEN_CLASS_INT;

			char* lex = (char*) malloc(sizeof(char) * 2);

			// out of memory
			if (!lex) {
				vseterrno(vENOMEM);
				return;
			}

			size_t bufferSize = 2;
			size_t idx = 0;

			while (isdigit(text[pos])) {
				if (bufferSize <= idx) {
					bufferSize *= 2;
					char* tmp = (char*) realloc(lex, sizeof(char*) * bufferSize);

					// out of memory upon realloc
					if (!tmp) {
						free(lex);
						vseterrno(vENOMEM);
						return;
					}

					lex = tmp;
				}

				lex[idx++] = text[pos++];
				parser_increment(text[pos - 1], &line, &col);

				// were on the end
				if (pos >= len) break;
			}

			// nul-terminate the string
			lex[idx] = '\0';
			// set the text
			tok.text = lex;

			// add this token
			TokenList_addToken(list, tok);
			// problem adding token
			if (verrno != 0) return;

			// re-iterate for next token
			continue;
		}

		// brackets
		if (ch == '[' || ch == ']' || ch == '(' || ch == ')' ||
			ch == '<' || ch == '>' || ch == '{' || ch == '}')
		{
			Token tok;
			tok.line = line;
			tok.col = col;
			tok.pos = pos;
			tok.type = TOKEN_TYPE_BRACKET;

			tok.text = (char*) malloc(sizeof(char) * 2);

			// allocation failed
			if (!tok.text) {
				vseterrno(vENOMEM);
				return;
			}

			tok.text[0] = ch;
			tok.text[1] = '\0';

			// set token class
			switch (ch) {
				case '[': tok.name = TOKEN_CLASS_OP_SQUARE; break;
				case ']': tok.name = TOKEN_CLASS_CL_SQUARE; break;
				case '(': tok.name = TOKEN_CLASS_OP_PAREN ; break;
				case ')': tok.name = TOKEN_CLASS_CL_PAREN ; break;
				case '<': tok.name = TOKEN_CLASS_OP_ANGLED; break;
				case '>': tok.name = TOKEN_CLASS_CL_ANGLED; break;
				case '{': tok.name = TOKEN_CLASS_OP_CURLY ; break;
				case '}': tok.name = TOKEN_CLASS_CL_CURLY ; break;
			}

			// add this token
			TokenList_addToken(list, tok);
			// problem adding token
			if (verrno != 0) return;

			col++;
			pos++;
			continue;
		}

		// operators
		if (ch == '.' || ch == ',' || ch == ':' || ch == '+' || ch == '-' || ch == '*' ||
			ch == '/' || ch == '&' || ch == '|' || ch == '<' || ch == '>' || ch == '=' ||
			ch == '^' || ch == '%' || ch == '~' || ch == '!')
		{
			Token tok;
			tok.line = line;
			tok.col = col;
			tok.type = TOKEN_TYPE_OPERATOR;
			char* lex;
			bool isDouble = false;

			// for double character operators, increment one more
			if (((ch == ':' || ch == '+' || ch == '-' || ch == '*' || ch == '&' || ch == '|' ||
				ch == '<' || ch == '>' || ch == '=') && text[pos + 1] == ch) ||
				((ch == '<' || ch == '>') && text[pos + 1] == '=') || // <= >=
				(ch == '-' && text[pos + 1] == '>')) // ->
			{
				col++;
				pos++;
				isDouble = true;
			}

			if (ch == '.') {
				lex = ".";
				tok.name = TOKEN_CLASS_DOT;
			}

			if (ch == ',') {
				lex = ",";
				tok.name = TOKEN_CLASS_COMMA;
			}

			if (ch == ':') {
				if (isDouble) {
					lex = "::";
					tok.name = TOKEN_CLASS_COLON_COLON;
				} else {
					lex = ":";
					tok.name = TOKEN_CLASS_COLON;
				}
			}

			if (ch == '+') {
				if (isDouble) {
					lex = "++";
					tok.name = TOKEN_CLASS_PLUS_PLUS;
				} else {
					lex = "+";
					tok.name = TOKEN_CLASS_PLUS;
				}
			}

			if (ch == '-') {
				if (isDouble) {
					if (text[pos] == '>') {
						lex = "->";
						tok.name = TOKEN_CLASS_MINUS_GREAT;
					} else {
						lex = "--";
						tok.name = TOKEN_CLASS_MINUS_MINUS;
					}
				} else {
					lex = "-";
					tok.name = TOKEN_CLASS_MINUS;
				}
			}

			if (ch == '*') {
				if (isDouble) {
					lex = "**";
					tok.name = TOKEN_CLASS_STAR_STAR;
				} else {
					lex = "*";
					tok.name = TOKEN_CLASS_STAR;
				}
			}

			if (ch == '/') {
				lex = "/";
				tok.name = TOKEN_CLASS_SLASH;
			}

			if (ch == '&') {
				if (isDouble) {
					lex = "&&";
					tok.name = TOKEN_CLASS_AND_AND;
				} else {
					lex = "&";
					tok.name = TOKEN_CLASS_AND;
				}
			}

			if (ch == '|') {
				if (isDouble) {
					lex = "||";
					tok.name = TOKEN_CLASS_OR_OR;
				} else {
					lex = "|";
					tok.name = TOKEN_CLASS_OR;
				}
			}

			if (ch == '<') {
				if (isDouble) {
					if (text[pos] == '=') {
						lex = "<=";
						tok.name = TOKEN_CLASS_LESS_EQUAL;
					} else {
						lex = "<<";
						tok.name = TOKEN_CLASS_LESS_LESS;
					}
				} else {
					lex = "<";
					tok.name = TOKEN_CLASS_LESS;
				}
			}

			if (ch == '>') {
				if (isDouble) {
					if (text[pos] == '=') {
						lex = ">=";
						tok.name = TOKEN_CLASS_GREAT_EQUAL;
					} else {
						lex = ">>";
						tok.name = TOKEN_CLASS_GREAT_GREAT;
					}
				} else {
					lex = ">";
					tok.name = TOKEN_CLASS_GREAT;
				}
			}

			if (ch == '=') {
				if (isDouble) {
					lex = "==";
					tok.name = TOKEN_CLASS_EQUAL_EQUAL;
				} else {
					lex = "=";
					tok.name = TOKEN_CLASS_EQUAL;
				}
			}

			if (ch == '^') {
				lex = "^";
				tok.name = TOKEN_CLASS_CARET;
			}

			if (ch == '%') {
				lex = "%";
				tok.name = TOKEN_CLASS_PERCENT;
			}

			if (ch == '~') {
				lex = "~";
				tok.name = TOKEN_CLASS_TILDE;
			}

			if (ch == '!') {
				lex = "!";
				tok.name = TOKEN_CLASS_EXCLAMATION;
			}

			// allocate heap for text
			tok.text = (char*) malloc(sizeof(char) * (strlen(lex) + 1));

			// memory allocation failed
			if (!tok.text) {
				vseterrno(vENOMEM);
				return;
			}

			strcpy((char*) tok.text, lex);

			// put this to token list
			TokenList_addToken(list, tok);
			// problem adding token
			if (verrno != 0) return;

			col++;
			pos++;
			continue;
		}

		// separator
		if (ch == ';') {
			Token tok;
			tok.line = line;
			tok.col = col;
			tok.pos = pos;
			tok.type = TOKEN_TYPE_SEPARATOR;
			// TokenList_destroy requires heap not stack
			tok.text = (char*) malloc(sizeof(char) * 2);

			// allocation failed!
			if (!tok.text) {
				vseterrno(vENOMEM);
				return;
			}

			// the text
			tok.text[0] = ch;
			tok.text[1] = '\0';

			// try to put this token on token list
			TokenList_addToken(list, tok);
			// problem adding token
			if (verrno != 0) return;

			pos++;
			col++;
			continue;
		}

		// TODO: complete this part

		parser_increment(ch, &line, &col);
		pos++;
	}

#ifdef __DEBUG
	for (int i = 0; i < list->length; i++) {
		printf("%s: %d %d\n", list->data[i].text, list->data[i].line, list->data[i].col);
	}
#endif // __DEBUG

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
