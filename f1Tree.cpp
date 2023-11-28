#include <unordered_map>
#include <string.h>
#include "langBNF.h"
#include "langTree.h"
#include "f1Consts.h"
using namespace std;

void traverse(Node*);

unordered_map<string, char> vars;

void decorate(Node* sel) {
	vars.clear();
	traverse(sel);
	for (auto &v: vars) {
		if (v.second == 2) {
			throw runtime_error(
				"1: SEMANTIC ERROR: Variable "
				+ v.first + " not declared");
		}
	}
}

void traverse(Node* sel) {
	if (sel == NULL) return;
	for (int i = 0; i < 2; i++) {
		if (sel->token[i] == NULL)
			break;
		if (sel->token[i]->type == idToken) {
			string name = sel->token[i]->instance;
			if (strcmp(sel->type, "vars") == 0
				|| strcmp(sel->type, "varList") == 0) {
				if (vars[name] & 1) {
					throw runtime_error(to_string(sel->token[i]->line)
						+ ": SEMANTIC ERROR: Redefinition of "
						+ name);
				}
				vars[name] |= 1; // declare
			} else {
				vars[name] |= 2; // use
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		if (sel->nont[i] == NULL)
			break;
		decorate(sel->nont[i]);
	}
}