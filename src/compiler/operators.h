#ifndef __VYTLANG_COMPILER_OPERATORS_H
#define __VYTLANG_COMPILER_OPERATORS_H

typedef enum {
	OPERATOR_PTR, // unary *a
	OPERATOR_REF, // unary &a
	OPERATOR_DOT, // binary a.b
	OPERATOR_SBC, // binary a[b]
	OPERATOR_SCP, // binary a :: b
	OPERATOR_PGT, // binary a -> b
	OPERATOR_COM, // binary a, b
	OPERATOR_ADD, // binary a + b
	OPERATOR_SUB, // binary a - b
	OPERATOR_MUL, // binary a * b
	OPERATOR_DIV, // binary a / b
	OPERATOR_MOD, // binary a % b
	OPERATOR_EXP, // binary a ** b
	OPERATOR_BND, // binary a & b
	OPERATOR_BOR, // binary a | b
	OPERATOR_BXR, // binary a ^ b
	OPERATOR_BNT, // unary ~a
	OPERATOR_BSL, // binary a << b
	OPERATOR_BSR, // binary a >> b
	OPERATOR_LIC, // unary ++a
	OPERATOR_LDC, // unary --a
	OPERATOR_RIC, // unary a++
	OPERATOR_RDC, // unary a--
	OPERATOR_LND, // binary a && b
	OPERATOR_LOR, // binary a || b
	OPERATOR_LNT, // binary !a
	OPERATOR_ASG, // binary a = b
	OPERATOR_CEQ, // binary a == b
	OPERATOR_CLT, // binary a < b
	OPERATOR_CGT, // binary a > b
	OPERATOR_CLQ, // binary a <= b
	OPERATOR_CGQ, // binary a >= b
	OPERATOR_LBL, // binary a: b
} VylOperator;

// operators precedence
extern const int opsPrecedence[];

#endif // __VYTLANG_COMPILER_OPERATORS_H
