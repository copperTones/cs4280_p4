#ifndef NODE_H
#define NODE_H
#include <string>
#include "token.h"
using namespace std;

// please ignore the class-like relation
typedef struct Node {
	string (*type)(Node*);
	Node* nont[4];
	Token* token[2];
} Node;
// string gen_func(*Node); Generator g = &gen_func;
typedef string (*Generator)(Node*);

#endif
