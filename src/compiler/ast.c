#include "ast.h"
#include "token.h"
#include "../err.h"
#include <stdbool.h>
#include <stdlib.h>

ASTNode* AST_createNode(Token* token, ASTNodeType type) {
	ASTNode* node = NULL;
	node->token = token;
	node->type = type;
	node->subNodes = (ASTNode*) malloc(sizeof(ASTNode) * 2);

	if (!node->subNodes) {
		vseterrno(vENOMEM);
		return NULL;
	}

	node->length = 0;
	node->__buffer = 2;
	return node;
}

void AST_addNode(ASTNode* tree, ASTNode* item) {
	// we're getting out of space
	if (tree->length >= tree->__buffer) {
		tree->__buffer *= 2;
		ASTNode* tmp = (ASTNode*) realloc(tree->subNodes, sizeof(ASTNode) * tree->__buffer);

		// realloc failed
		if (!tmp) {
			vseterrno(vENOMEM);
			free(tree->subNodes);
			return;
		}

		tree->subNodes = tmp;
	}

	tree->subNodes[tree->length++] = *item;
}

ASTNode* AST_createTree(TokenList* list) {
	size_t idx = 0;
	ASTNode* root = AST_createNode(NULL, AST_NODE_TYPE_ROOT_NODE);
	AST_addNode(root, __AST_makeTree(list, &idx, 0));

	if (verrno != 0) {
		AST_destroyTree(root);
		return NULL;
	}

	return root;
}

void AST_destroyTree(ASTNode* tree) {
	if (!tree) return;
	for (int i = 0; i < tree->length; i++) AST_destroyTree(&tree->subNodes[i]);
	if (tree->token && tree->token->text) free(tree->token->text);
	free(tree->subNodes);
}

ASTNode* __AST_makeTree(TokenList* list, size_t* idx, int minPrec) {
	if (*idx >= list->length) {
		vseterrno(vEPEND);
		return NULL;
	}

	// TODO: work on it

	return NULL;
}
