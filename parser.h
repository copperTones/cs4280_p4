#include "token.h"
using namespace std;

extern Token next;

int parser();
void require(int);
void require(int, char*);
void errMsg();
void nont_start();
