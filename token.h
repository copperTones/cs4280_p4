#ifndef TOKEN_H
#define TOKEN_H

typedef struct Token {
	int type;
	char instance[9];
	int line;
} Token;

#endif
