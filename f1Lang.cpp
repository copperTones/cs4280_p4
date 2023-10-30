#include <ctype.h>
#include <string.h>
#include "language.h"

const int classSep = 1000;
const int tableWidth = 10;
const int fsaTable[] = {
/* 0     1     2     3     4     5     6     7     8     9
  \0    \s    \w     ?    \d     <     >     =    op     #  */
2000,    0,    1, 1000,    2,    3,    3,    4,    4,    5, // 0
2001, 2001,    1, 1000,    1, 2001, 2001, 2001, 2001, 2001, // 1
2002, 2002, 1001, 1000,    2, 2002, 2002, 2002, 2002, 2002, // 2
2003, 2003, 2003, 1000, 2003, 2003, 2003,    4, 2003, 2003, // 3
2003, 2003, 2003, 1000, 2003, 2003, 2003, 2003, 2003, 2003, // 4
1002,    5,    5,    5,    5,    5,    5,    5,    5,    6, // 5
2100, 2100, 2100, 2100, 2100, 2100, 2100, 2100, 2100, 2100  // 6
};

const char* sortedKeyw[] = {
"cond",
"end",
"func",
"let",
"loop",
"main",
"print",
"scan",
"start",
"stop",
"then",
"var",
"void"
};

int charMap(char c) {
	switch (c) {
	case -1:
		return 0;
	case '<':
		return 5;
	case '>':
		return 6;
	case '=':
		return 7;
	case '(':
	case ')':
	case '*':
	case '+':
	case ',':
	case '-':
	case '.':
	case '/':
	case ':':
	case ';':
	case '[':
	case ']':
	case '{':
	case '}':
	case '%':
	case '~':
		return 8;
	case '#':
		return 9;
	}
	if (isspace(c))
		return 1;
	if (isalpha(c))
		return 2;
	if (isdigit(c))
		return 4;
	return 3;
}

int filterToken(int type, char *instance) {
	if (type == 100)
		return -1;
	if (type != 1)
		return type;

	// binary search!
	int top = 0, bot = 13, mid, m;
	while (1) {
		mid = (bot + top)/2;
		m = strcmp(instance, sortedKeyw[mid]);
		if (bot == top+1 && m != 0) {
			// not in list -> idToken
			return 1;
		} else if (m > 0) {
			top = mid;
		} else if (m == 0) {
			return mid + 4;
		} else if (m < 0) {
			bot = mid;
		}
	}
}
