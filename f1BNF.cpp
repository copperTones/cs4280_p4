#include <iostream>
#include <string.h>
#include "parser.h"
#include "langBNF.h"
#include "f1Consts.h"
using namespace std;

void nont_vars();
void nont_varList();
void nont_exp();
void nont_exp2();
void nont_exp3();
void nont_exp4();
void nont_stats();
void nont_stats2();
void nont_stat();
void nont_block();
void nont_in();
void nont_out();
void nont_if();
void nont_loop();
void nont_assign();
void nont_relOp();

void nont_start() {
cout << "start\n";
	nont_vars();
	require(mainToken);
	nont_stats();
	require(endToken);
}

void nont_vars() {
cout << "vars\n";
	if (next.type == letToken) {
		require(letToken);
		require(idToken);
		require(opToken, "=");
		require(intToken);
		nont_varList();
		require(opToken, ".");
	}
}

void nont_varList() {
cout << "varList\n";
	if (next.type == idToken) {
		require(idToken);
		require(opToken, "=");
		require(intToken);
		nont_varList();
	}
}

void nont_exp() {
cout << "exp\n";
	nont_exp2();
	if (next.type == opToken && strcmp(next.instance, "+") == 0) {
		require(opToken);
		nont_exp();
	} else if (next.type == opToken && strcmp(next.instance, "-") == 0) {
		require(opToken);
		nont_exp();
	}
}

void nont_exp2() {
cout << "exp2\n";
	nont_exp3();
	if (next.type == opToken && strcmp(next.instance, "*") == 0) {
		require(opToken);
		nont_exp2();
	}
}

void nont_exp3() {
cout << "exp3\n";
	if (next.type == opToken && strcmp(next.instance, "-") == 0) {
		require(opToken);
		nont_exp3();
	} else {
		nont_exp4();
		if (next.type == opToken && strcmp(next.instance, "/") == 0) {
			require(opToken);
			nont_exp3();
		}
	}
}

void nont_exp4() {
cout << "exp4\n";
	if (next.type == opToken && strcmp(next.instance, "[") == 0) {
		require(opToken);
		nont_exp();
		require(opToken, "]");
	} else if (next.type == intToken) {
		require(intToken);
	} else {
		require(idToken);
	}
}

void nont_stats() {
cout << "stats\n";
	nont_stat();
	nont_stats2();
}

void nont_stats2() {
cout << "stats2\n";
	switch (next.type) {
		case startToken:
		case scanToken:
		case printToken:
		case condToken:
		case loopToken:
		case idToken:
			nont_stat();
			nont_stats2();
			break;
	}
}

void nont_stat() {
cout << "stat\n";
	switch (next.type) {
		case startToken:
			nont_block();
			break;
		case scanToken:
			nont_in();
			break;
		case printToken:
			nont_out();
			break;
		case condToken:
			nont_if();
			break;
		case loopToken:
			nont_loop();
			break;
		case idToken:
			nont_assign();
			break;
		default:
			cout << next.type << " not of "
				<< startToken << " "
				<< scanToken << " "
				<< printToken << " "
				<< condToken << " "
				<< loopToken << " "
				<< idToken << "\n";
			errMsg();
			break;
	}
}

void nont_block() {
cout << "block\n";
	require(startToken);
	nont_vars();
	nont_stats();
	require(stopToken);
}

void nont_in() {
cout << "in\n";
	require(scanToken);
	require(idToken);
	require(opToken, ".");
}

void nont_out() {
cout << "out\n";
	require(printToken);
	nont_exp();
	require(opToken, ".");
}

void nont_if() {
cout << "if\n";
	require(condToken);
	require(opToken, "(");
	nont_exp();
	nont_relOp();
	nont_exp();
	require(opToken, ")");
	nont_stat();
}

void nont_loop() {
cout << "loop\n";
	require(loopToken);
	require(opToken, "(");
	nont_exp();
	nont_relOp();
	nont_exp();
	require(opToken, ")");
	nont_stat();
}

void nont_assign() {
cout << "assign\n";
	require(idToken);
	require(opToken, "~");
	nont_exp();
	require(opToken, ".");
}

void nont_relOp() {
cout << "relOp\n";
	switch (next.instance[0]) {
		case '<':
		case '>':
		case '=':
		case '~':
			require(opToken);
			break;
	default:
		errMsg();
	}
}
