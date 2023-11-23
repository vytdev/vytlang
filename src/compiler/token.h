#ifndef __VYTLANG_COMPILER_TOKEN_H
#define __VYTLANG_COMPILER_TOKEN_H

#include <stddef.h>

typedef enum {
	TOKEN_TYPE_OPERATOR,
	TOKEN_TYPE_IDENTIFIER,
	TOKEN_TYPE_KEYWORD,
	TOKEN_TYPE_BRACKET,
	TOKEN_TYPE_SEPARATOR,
	TOKEN_TYPE_LITERAL,
} TokenType;

typedef enum {
	TOKEN_CLASS_IDENTIFIER,
	// keywords
	TOKEN_CLASS_KIF,
	TOKEN_CLASS_KELSE,
	TOKEN_CLASS_KTRY,
	TOKEN_CLASS_KCATCH,
	TOKEN_CLASS_KFINALLY,
	TOKEN_CLASS_KSWITCH,
	TOKEN_CLASS_KCASE,
	TOKEN_CLASS_KWITH,
	TOKEN_CLASS_KDO,
	TOKEN_CLASS_KWHILE,
	TOKEN_CLASS_KFOR,
	TOKEN_CLASS_KBREAK,
	TOKEN_CLASS_KCONTINUE,
	TOKEN_CLASS_KDELETE,
	TOKEN_CLASS_KNEW,
	TOKEN_CLASS_KUSING,
	TOKEN_CLASS_KIMPORT,
	TOKEN_CLASS_KEXPORT,
	TOKEN_CLASS_KEXPOSE,
	TOKEN_CLASS_KVAR,
	TOKEN_CLASS_KNAMESPACE,
	TOKEN_CLASS_KFUNCTION,
	TOKEN_CLASS_KTHROW,
	TOKEN_CLASS_KRETURN,
	TOKEN_CLASS_KCLASS,
	TOKEN_CLASS_KEXTENDS,
	TOKEN_CLASS_KIMPLEMENTS,
	TOKEN_CLASS_KPUBLIC,
	TOKEN_CLASS_KPRIVATE,
	TOKEN_CLASS_KPROTECTED,
	TOKEN_CLASS_KSTATIC,
	TOKEN_CLASS_KDYNAMIC,
	TOKEN_CLASS_KABSTRACT,
	TOKEN_CLASS_KOVERRIDE,
	TOKEN_CLASS_KENUM,
	TOKEN_CLASS_KINTERFACE,
	TOKEN_CLASS_KTYPE,
	TOKEN_CLASS_KKEYOF,
	TOKEN_CLASS_KCONST,
	TOKEN_CLASS_KTEMPLATE,
	// literals
	TOKEN_CLASS_INT,
	// brackets
	TOKEN_CLASS_OP_SQUARE,   // [
	TOKEN_CLASS_CL_SQUARE,   // ]
	TOKEN_CLASS_OP_PAREN ,   // (
	TOKEN_CLASS_CL_PAREN ,   // )
	TOKEN_CLASS_OP_ANGLED,   // <
	TOKEN_CLASS_CL_ANGLED,   // >
	TOKEN_CLASS_OP_CURLY ,   // {
	TOKEN_CLASS_CL_CURLY ,   // }
	// operators
	TOKEN_CLASS_DOT,         // .
	TOKEN_CLASS_COMMA,       // ,
	TOKEN_CLASS_COLON,       // :
	TOKEN_CLASS_COLON_COLON, // ::
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
