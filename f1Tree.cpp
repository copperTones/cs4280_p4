#include "langBNF.h"
#include "langTree.h"
#include "f1Consts.h"
#include "f1Gen.h"
using namespace std;

void traverse(Node*);

unordered_map<string, Declaration> vars;

void decorate(Node* sel) {
	vars.clear();
	traverse(sel);
	for (auto &v: vars) {
		if (v.second.flags == 2) {
			throw runtime_error(
				"1: SEMANTIC ERROR: Variable "
				+ v.first + " not declared");
		}
	}
}

void traverse(Node* sel) {
	if (sel == NULL) return;
	if ((sel->type == &gen_vars
		|| sel->type == &gen_varList)) {
		// declaring variables
		string name = sel->token[0]->instance;
		if (vars[name].flags & 1) {
			throw runtime_error(to_string(sel->token[0]->line)
				+ ": SEMANTIC ERROR: Redefinition of "
				+ name);
		}
		vars[name].flags |= 1;
		vars[name].value = sel->token[1]->instance;
	} else {
		// search for use
		for (int i = 0; i < 2; i++) {
			if (sel->token[i] == NULL)
				break;
			if (sel->token[i]->type == idToken) {
				vars[sel->token[i]->instance].flags |= 2; // use
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		if (sel->nont[i] == NULL)
			break;
		traverse(sel->nont[i]);
	}
}
