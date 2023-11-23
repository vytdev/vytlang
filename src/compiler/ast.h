#ifndef __VYTLANG_COMPILER_AST_H
#define __VYTLANG_COMPILER_AST_H

#include "token.h"
#include <stddef.h>
#include <stdbool.h>

// ast node types
typedef enum {
	// the root of source file
	AST_NODE_TYPE_ROOT_NODE,
	// literals, identifiers, etc.
	AST_NODE_TYPE_LEAF_NODE,
	// trunk of our statements
	AST_NODE_TYPE_BLOCK_NODE,
	// the branches, like declarations, loops, etc.
	AST_NODE_TYPE_STATEMENT_NODE,
	// the stem nodes
	AST_NODE_TYPE_UNARY_OPERATOR,
	AST_NODE_TYPE_BINARY_OPERATOR,
} ASTNodeType;

// our ast node
typedef struct __ASTNode_s {
	Token* token;
	ASTNodeType type;
	struct __ASTNode_s* subNodes;
	size_t length;
	size_t __buffer;
} ASTNode;

// create an ast node
ASTNode* AST_createNode(Token* token, ASTNodeType type);

// add an ast node into another ast tree
void AST_addNode(ASTNode* tree, ASTNode* item);

// create ast tree from given token list
ASTNode* AST_createTree(TokenList* list);

// free heap memory used by ast tree
void AST_destroyTree(ASTNode* tree);

// internal function to generate ast tree
// the AST_createTree function is just a wrapper
ASTNode* __AST_makeTree(TokenList* list, size_t* idx, int minPrec);

#endif // __VYTLANG_COMPILER_AST_H
