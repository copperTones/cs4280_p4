#include "token.h"
#include "node.h"

extern Token nextTk;

Node* parser();
void require(int);
void require(int, const char*);
Token* match(int);
Token* match(int, const char*);
void errMsg();
