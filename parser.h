#include "token.h"
using namespace std;

extern Token next;
extern const char *tokenNames[];

int parser();
void require(int);
void require(int, const char*);
void errMsg();
void nont_start();
