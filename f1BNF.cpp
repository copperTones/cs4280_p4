#include <iostream>
#include <string.h>
#include "parser.h"
#include "langBNF.h"
#include "f1Consts.h"
using namespace std;

Node* nont_vars();
Node* nont_varList();
Node* nont_exp();
Node* nont_exp2();
Node* nont_exp3();
Node* nont_exp4();
Node* nont_stats();
Node* nont_stats2();
Node* nont_stat();
Node* nont_block();
Node* nont_in();
Node* nont_out();
Node* nont_if();
Node* nont_loop();
Node* nont_assign();
Node* nont_relOp();

Node* nont_start() {
	Node* node = new Node();
	strcpy(node->type, "start");
	node->nont[0] = nont_vars();
	require(mainToken);
	node->nont[1] = nont_stats();
	require(endToken);
	return node;
}

Node* nont_vars() {
	Node* node = new Node();
	strcpy(node->type, "vars");
	if (next.type == letToken) {
		require(letToken);
		node->token[0] = match(idToken);
		require(opToken, "=");
		node->token[1] = match(intToken);
		node->nont[0] = nont_varList();
		require(opToken, ".");
	}
	return node;
}

Node* nont_varList() {
	Node* node = new Node();
	strcpy(node->type, "varList");
	if (next.type == idToken) {
		node->token[0] = match(idToken);
		require(opToken, "=");
		node->token[1] = match(intToken);
		node->nont[0] = nont_varList();
	}
	return node;
}

Node* nont_exp() {
	Node* node = new Node();
	strcpy(node->type, "exp");
	node->nont[0] = nont_exp2();
	if (next.type == opToken && strcmp(next.instance, "+") == 0) {
		node->token[0] = match(opToken);
		node->nont[1] = nont_exp();
	} else if (next.type == opToken && strcmp(next.instance, "-") == 0) {
		node->token[0] = match(opToken);
		node->nont[1] = nont_exp();
	}
	return node;
}

Node* nont_exp2() {
	Node* node = new Node();
	strcpy(node->type, "exp2");
	node->nont[0] = nont_exp3();
	if (next.type == opToken && strcmp(next.instance, "*") == 0) {
		node->token[0] = match(opToken);
		node->nont[1] = nont_exp2();
	}
	return node;
}

Node* nont_exp3() {
	Node* node = new Node();
	strcpy(node->type, "exp3");
	if (next.type == opToken && strcmp(next.instance, "-") == 0) {
		node->token[0] = match(opToken);
		node->nont[0] = nont_exp3();
	} else {
		node->nont[0] = nont_exp4();
		if (next.type == opToken && strcmp(next.instance, "/") == 0) {
			node->token[0] = match(opToken);
			node->nont[1] = nont_exp3();
		}
	}
	return node;
}

Node* nont_exp4() {
	Node* node = new Node();
	strcpy(node->type, "exp4");
	if (next.type == opToken && strcmp(next.instance, "[") == 0) {
		require(opToken);
		node->nont[0] = nont_exp();
		require(opToken, "]");
	} else if (next.type == intToken) {
		node->token[0] = match(intToken);
	} else {
		node->token[0] = match(idToken);
	}
	return node;
}

Node* nont_stats() {
	Node* node = new Node();
	strcpy(node->type, "stats");
	node->nont[0] = nont_stat();
	node->nont[1] = nont_stats2();
	return node;
}

Node* nont_stats2() {
	Node* node = new Node();
	strcpy(node->type, "stats2");
	switch (next.type) {
		case startToken:
		case scanToken:
		case printToken:
		case condToken:
		case loopToken:
		case idToken:
			node->nont[0] = nont_stat();
			node->nont[1] = nont_stats2();
			break;
	}
	return node;
}

Node* nont_stat() {
	Node* node = new Node();
	strcpy(node->type, "stat");
	switch (next.type) {
		case startToken:
			node->nont[0] = nont_block();
			break;
		case scanToken:
			node->nont[0] = nont_in();
			break;
		case printToken:
			node->nont[0] = nont_out();
			break;
		case condToken:
			node->nont[0] = nont_if();
			break;
		case loopToken:
			node->nont[0] = nont_loop();
			break;
		case idToken:
			node->nont[0] = nont_assign();
			break;
		default:
			errMsg();
			break;
	}
	return node;
}

Node* nont_block() {
	Node* node = new Node();
	strcpy(node->type, "block");
	require(startToken);
	node->nont[0] = nont_vars();
	node->nont[1] = nont_stats();
	require(stopToken);
	return node;
}

Node* nont_in() {
	Node* node = new Node();
	strcpy(node->type, "in");
	require(scanToken);
	node->token[0] = match(idToken);
	require(opToken, ".");
	return node;
}

Node* nont_out() {
	Node* node = new Node();
	strcpy(node->type, "out");
	require(printToken);
	node->nont[0] = nont_exp();
	require(opToken, ".");
	return node;
}

Node* nont_if() {
	Node* node = new Node();
	strcpy(node->type, "if");
	require(condToken);
	require(opToken, "(");
	node->nont[0] = nont_exp();
	node->nont[1] = nont_relOp();
	node->nont[2] = nont_exp();
	require(opToken, ")");
	node->nont[3] = nont_stat();
	return node;
}

Node* nont_loop() {
	Node* node = new Node();
	strcpy(node->type, "loop");
	require(loopToken);
	require(opToken, "(");
	node->nont[0] = nont_exp();
	node->nont[1] = nont_relOp();
	node->nont[2] = nont_exp();
	require(opToken, ")");
	node->nont[3] = nont_stat();
	return node;
}

Node* nont_assign() {
	Node* node = new Node();
	strcpy(node->type, "assign");
	node->token[0] = match(idToken);
	require(opToken, "~");
	node->nont[0] = nont_exp();
	require(opToken, ".");
	return node;
}

Node* nont_relOp() {
	Node* node = new Node();
	strcpy(node->type, "relOp");
	switch (next.instance[0]) {
		case '<':
		case '>':
		case '=':
		case '~':
			node->token[0] = match(opToken);
			break;
	default:
		errMsg();
	}
	return node;
}
