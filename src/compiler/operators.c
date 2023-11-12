#include "operators.h"

// operators precedence, used on ast
const int opsPrecedence[] = {
	[OPERATOR_PTR] = 19, // unary  *a
	[OPERATOR_REF] = 19, // unary  &a
	[OPERATOR_DOT] = 20, // binary a.b
	[OPERATOR_SBC] = 20, // binary a[b]
	[OPERATOR_SCP] = 20, // binary a :: b
	[OPERATOR_PGT] = 20, // binary a -> b
	[OPERATOR_COM] = 18, // binary a, b
	[OPERATOR_ADD] = 12, // binary a + b
	[OPERATOR_SUB] = 12, // binary a - b
	[OPERATOR_MUL] = 13, // binary a * b
	[OPERATOR_DIV] = 13, // binary a / b
	[OPERATOR_MOD] = 13, // binary a % b
	[OPERATOR_EXP] = 14, // binary a ** b
	[OPERATOR_BND] = 17, // binary a & b
	[OPERATOR_BOR] = 16, // binary a | b
	[OPERATOR_BXR] = 16, // binary a ^ b
	[OPERATOR_BNT] = 18, // unary  ~a
	[OPERATOR_BSL] = 16, // binary a << b
	[OPERATOR_BSR] = 15, // binary a >> b
	[OPERATOR_LIC] = 18, // unary  ++a
	[OPERATOR_LDC] = 18, // unary  --a
	[OPERATOR_RIC] = 18, // unary  a++
	[OPERATOR_RDC] = 18, // unary  a--
	[OPERATOR_LND] = 9,  // binary a && b
	[OPERATOR_LOR] = 9,  // binary a || b
	[OPERATOR_LNT] = 10, // binary !a
	[OPERATOR_ASG] = 1 , // binary a = b
	[OPERATOR_CEQ] = 11, // binary a == b
	[OPERATOR_CLT] = 11, // binary a < b
	[OPERATOR_CGT] = 11, // binary a > b
	[OPERATOR_CLQ] = 11, // binary a <= b
	[OPERATOR_CGQ] = 11, // binary a >= b
	[OPERATOR_LBL] = 1 , // binary a: b
};
