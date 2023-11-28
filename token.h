#ifndef TOKEN_H
#define TOKEN_H
#include <string>
using namespace std;

typedef struct Token {
	int type;
	string instance;
	int line;
} Token;

#endif
