#ifndef __VYTLANG_ERR_H
#define __VYTLANG_ERR_H

// our errno
typedef enum {
	// generic
	vEMPTY, // no error
	vENOMEM, // insufficient memory
	vENOENT, // no such file or directory
	// parser specific
	vEPUCMT, // unterminated comment
} Verrcode;

// the constant
extern Verrcode verrno;

// set verrno to a specific error
void vseterrno(Verrcode err);

// print the error message
void vperror();

#endif // __VYTLANG_ERR_H