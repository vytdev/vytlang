#ifndef __VYTLANG_ERR_H
#define __VYTLANG_ERR_H

// our errno
typedef enum {
	// generic
	vEMPTY, // no error
	vENOMEM, // insufficient memory
	vENOENT, // no such file or directory
	vEREAD, // read error
	// parser specific
	vEPUCMT, // unterminated comment
} Verrcode;

// the constant
extern Verrcode verrno;
// additional message
extern char* verrmsg;

// set verrno to a specific error
void vseterrno(Verrcode err);

// set verrmsg additional message
void vseterrmsg(const char* msg, ...);

// print the error message
void vperror(void);

#endif // __VYTLANG_ERR_H
