#include <iostream>
#include "langBNF.h"
using namespace std;

void printTree(Node* sel, int lvl) {
	if (sel == NULL) return;
	for (int i = 0; i < lvl; i++)
		cout << "  ";
	cout << sel->type << ":";
	for (int i = 0; i < 2; i++) {
		if (sel->token[i] == NULL)
			break;
		cout << " " << tokenNames[sel->token[i]->type]
		<< " \"" << sel->token[i]->instance << "\"";
	}
	cout << "\n";
	for (int i = 0; i < 4; i++) {
		if (sel->nont[i] == NULL)
			break;
		printTree(sel->nont[i], lvl + 1);
	}
}
