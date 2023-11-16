#include <string.h>
#include <stdio.h>
#include <stdexcept>
#include "scanner.h"
#include "parser.h"
#include "langBNF.h"

Token next;

int parser() {
	next = nextToken();
	nont_start();
	if (next.type != 0) { // EOF
		// not willing to reformat to c++ strings
		char err[100];
		sprintf(err, "%d: PARSER ERROR: Expected EOF, got %s \"%s\" instead",
			next.line,
			tokenNames[next.type],
			next.instance);
		throw runtime_error(err);
	}
	return 0;
}

void require(int type) {
	if (type != next.type) {
		errMsg();
	}
	next = nextToken();
}

void require(int type, const char* instance) {
	if (type != next.type || strcmp(instance, next.instance) != 0) {
		errMsg();
	}
	next = nextToken();
}

void errMsg() {
	// not willing to reformat to c++ strings
	char err[100];
	sprintf(err, "%d: PARSER ERROR: Unexpected token %s \"%s\"",
		next.line,
		tokenNames[next.type],
		next.instance);
	throw runtime_error(err);
}
