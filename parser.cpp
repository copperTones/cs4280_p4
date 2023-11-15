#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "scanner.h"
#include "parser.h"
#include "langBNF.h"

Token next;

int parser() {
	next = nextToken();
	nont_start();
	if (next.type == 0) // EOF
		return 0;
	return -1;
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
	cout << next.line << ": PARSER ERROR: Unexpected token "
	<< tokenNames[next.type] << " "
	<< next.instance << "\n";
	// cleanup?
	exit(1);
}
