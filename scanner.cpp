#include "scanner.h"
#include "langToken.h"

istream* inp;
int line;

void scanFile(istream* ninp) {
	inp = ninp;
	line = 1;
}

Token nextToken() {
	Token next;
	next.type = -1;

	// filter can discard, ie. comments
	while (next.type == -1) {
		next.instance == "";
		int state = 0, ci = 0, t, act;
		char c;
		while (1) {
			c = inp->get();
			t = charMap(c);
			act = fsaTable[t + state*tableWidth];
			if (act >= 2*classSep) {
				// 2000s - end token
				next.type = act - 2*classSep;
				next.line = line;
				inp->unget();
				break;
			} else if (act >= classSep) {
				// 1000s - error
				next.type = act;
				next.line = line;
				inp->unget();
				break; // we don't deal with it
			} else {
				// 0000s - jump
				if (act != 0 && ci < 8) {
					next.instance += c;
					ci++;
				}
				state = act;
				if (c == '\n')
					line++;
			}
		}
		next.type = filterToken(next);
	}

	return next;
}
