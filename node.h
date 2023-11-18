#ifndef NODE_H
#define NODE_H
#include "token.h"

typedef struct Node {
	char type[9];
	Node* nont[4];
	Token* token[2];
} Node;

#endif
