#ifndef __VYTLANG_MAIN_H
#define __VYTLANG_MAIN_H

#include <stdbool.h>

// type definitions of the structure of TermOpts object
struct __TermOpts_s {
	// where positional arguments found
	int argp;
	int argc;
	char** argv;

	// do we parsed atleast one option?
	bool hasOpt;
	// whether to read file from stdin
	bool readFromStdin;
	// only show help
	bool showHelp;
	// show version then exit
	bool showVersion;
};

// the variable that contain the argument info supplied from terminal
// call to this command
extern struct __TermOpts_s TermOpts;

// the entry point of our program
int main(int argc, char** argv);

// show help message
void showHelp(void);

// show version
void showVersion(void);

#endif // __VYTLANG_MAIN_H
