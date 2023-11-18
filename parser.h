#include "token.h"

extern Token next;

int parser();
void require(int);
void require(int, const char*);
Token* match(int);
Token* match(int, const char*);
void errMsg();
