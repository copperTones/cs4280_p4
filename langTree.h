#include <unordered_map>
#include "node.h"

typedef struct Declaration {
	char flags;
	string value;
} Declaration;

extern unordered_map<string, Declaration> vars;

void decorate(Node*);
