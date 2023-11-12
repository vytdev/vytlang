#ifndef __VYTLANG_UTIL_H
#define __VYTLANG_UTIL_H

#include <stdlib.h>

#ifdef _WIN32
#   include <io.h>
#   define STDIN_TTY _isatty(_fileno(stdin))
#else
#   include <unistd.h>
#   define STDIN_TTY isatty(fileno(stdin))
#endif // _WIN32

// read file as ascii
char* util_readFile(const char* path);

// read from stdin
char* util_readStdIn(void);

#endif // __VYTLANG_UTIL_H
