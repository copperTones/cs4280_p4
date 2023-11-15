#include "token.h"

extern Token next;

int parser();
void require(int);
void require(int, const char*);
void errMsg();
