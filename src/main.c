#include "main.h"
#include "config.h"
#include "util.h"
#include "err.h"
#include "compiler/parser.h"
#include "compiler/token.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>

// terminal options
struct __TermOpts_s TermOpts = {
	.argp = -1,
	.hasOpt = false,
	.readFromStdin = false,
	.showHelp = false,
	.showVersion = false,
};

int main(int argc, char** argv) {

	// make these accessible by other modules
	TermOpts.argc = argc;
	TermOpts.argv = argv;

	// parse cli args
	for (int i = 1; i < argc; i++) {
		char* arg = argv[i];
		size_t len = strlen(arg);

		// this is not an option
		if (len == 0 || arg[0] != '-') {
			TermOpts.argp = i;
			break;
		}

		// we found an option
		TermOpts.hasOpt = true;

		// a single dash, means read from stdin: -
		if (len == 1) {
			TermOpts.readFromStdin = true;
			continue;
		}

		// found a double dash delimeter! --
		if (len == 2 && arg[1] == arg[0]) {
			// there's arguments
			if (i < (argc - 1)) TermOpts.argp = i + 1;
			break;
		}

		// let's process the options raw!

		// show help option, equivalent with -h flag
		if (strcmp(arg, "--help") == 0) {
			TermOpts.showHelp = true;
			continue;
		}

		// show version option, equivalent with -v flag
		if (strcmp(arg, "--version") == 0) {
			TermOpts.showVersion = true;
			continue;
		}

		// unknown option
		if (arg[1] == arg[0]) {
			fprintf(stderr, "vyt: unknown option %s\n", arg);
			return 2;
		}

		// for short flags:
		for (int j = 1; j < len; j++) switch (arg[j]) {
			case 'h': TermOpts.showHelp = true; break;
			case 'v': TermOpts.showVersion = true; break;
			default: fprintf(stderr, "vyt: unrecognized flag -- %c\n", arg[j]); return 2;
		}
	}

	// there are no arguments
	if (TermOpts.argp == -1) {
		TermOpts.readFromStdin = true;
	}

	// show help
	if (TermOpts.showHelp) {
		showHelp();
		// exit with exit code 1, just follow common convention
		return 1;
	}

	// show version
	if (TermOpts.showVersion) {
		showVersion();
		return 0;
	}




	// the program run

	char* text;

	if (TermOpts.readFromStdin) {
		if (STDIN_TTY) {
			fprintf(stderr, "vyt: repl: not implemented\n");
			return 1;
		}

		text = util_readStdIn();
	}
	else {
		if (TermOpts.argp == -1) {
			fprintf(stderr, "vyt: please provide file\n");
			return 1;
		}
		text = util_readFile(argv[TermOpts.argp]);
	}

	// an error happened after reading file
	if (verrno != 0) {
		vperror();
		return 1;
	}

	// create token list
	TokenList list;
	TokenList_create(&list);

	// token list not created
	if (verrno != 0) {
		vperror();
		return 1;
	}

	// tokenize the source
	tokenize(text, &list);

	// an error happened during tokenization
	if (verrno != 0) {
		vperror();
		return 1;
	}

	// post cleanup
	TokenList_destroy(&list);
	free(text);

	return 0;
}

void showHelp(void) {
	fprintf(stderr,
		"VYT Language %s\n"
		"    A custom programming language\n"
		"    https://github.com/vytdev/vytlang\n"
		"\n"
		"Usage: %s [options] [file | -] [args ...]\n"
		"\n"
		"Options:\n"
		"    -                      Read from stdin (default; repl if tty)\n"
		"        --                 End of vyl options\n"
		"    -h, --help             Show this help and exit\n"
		"    -v, --version          Show version name then exit\n"
		"\n"
		"Arguments:\n"
		"    file                   File to read and process\n"
		"    args                   Args to pass to the program\n"
		"\n"
		"Copyright (c) 2023, VYT. All rights reserved\n"
		"This project is under the GNU General Public License v3\n"
		"For details, see: http://github.com/vytdev/vytlang/blob/master/COPYING\n",
		// pass these format arguments
		VYL_VERSION, TermOpts.argv[0]
	);
}

void showVersion(void) {
	printf("VYT Language %s (build %d)\n", VYL_VERSION, VYL_BUILD);
}
