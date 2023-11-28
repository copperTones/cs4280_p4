#include <stdexcept>
#include <string>
#include "scanner.h"
#include "parser.h"
#include "langBNF.h"
using namespace std;

Token nextTk;

Node* parser() {
	nextTk = nextToken();
	Node* tree = nont_start();
	if (nextTk.type != 0) { // EOF
		throw runtime_error(to_string(nextTk.line)
			+ ": PARSER ERROR: Expected EOF, got "
			+ tokenNames[nextTk.type] + " \""
			+ nextTk.instance
			+ "\" instead");
	}
	return tree;
}

void require(int type) {
	if (type != nextTk.type) {
		errMsg();
	}
	nextTk = nextToken();
}

void require(int type, const char* instance) {
	if (type != nextTk.type || instance != nextTk.instance) {
		errMsg();
	}
	nextTk = nextToken();
}

Token* match(int type) {
	Token* token = new Token();
	*token = nextTk;
	require(type);
	return token;
}

Token* match(int type, const char* instance) {
	Token* token = new Token();
	*token = nextTk;
	require(type, instance);
	return token;
}

void errMsg() {
	throw runtime_error(to_string(nextTk.line)
		+ ": PARSER ERROR: Unexpected token "
		+ tokenNames[nextTk.type] + " \""
		+ nextTk.instance
		+ "\"");
}
