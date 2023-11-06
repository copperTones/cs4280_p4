#include "scanner.h"
#include "parser.h"

Token next;

int parser() {
	next = nextToken();
	nont_start();
	if (next.type == 0) // EOF
		return 0;
	return -1;
}
