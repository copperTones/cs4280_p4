#include <string.h>
#include <stdio.h>
#include <stdexcept>
#include "scanner.h"
#include "parser.h"
#include "langBNF.h"

Token next;

Node* parser() {
	next = nextToken();
	Node* tree = nont_start();
	if (next.type != 0) { // EOF
		// not willing to reformat to c++ strings
		char err[100];
		sprintf(err, "%d: PARSER ERROR: Expected EOF, got %s \"%s\" instead",
			next.line,
			tokenNames[next.type],
			next.instance);
		throw runtime_error(err);
	}
	return tree;
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

Token* match(int type) {
	Token* token = new Token();
	*token = next;
	require(type);
	return token;
}

Token* match(int type, const char* instance) {
	Token* token = new Token();
	*token = next;
	require(type, instance);
	return token;
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
