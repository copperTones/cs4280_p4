#include "langTree.h"
#include "f1Gen.h"

int labelId = 0;

string generate(Node* sel) {
	return sel->type(sel);
}

string gen_start(Node* sel) {
	string s = generate(sel->nont[1]);
	s += "STOP\n_ 0\n";
	for (auto &v: vars) {
		s += v.first;
		s += " " + v.second.value + "\n";
	}
	return s;
}

string gen_vars(Node* sel) {
	return "tmp"; //TODO
}

string gen_varList(Node* sel) {
	return "tmp"; //TODO
}

string gen_exp(Node* sel) {
	return "tmp"; //TODO
}

string gen_exp2(Node* sel) {
	return "tmp"; //TODO
}

string gen_exp3(Node* sel) {
	return "tmp"; //TODO
}

string gen_exp4(Node* sel) {
	return "tmp"; //TODO
}

string gen_stats(Node* sel) {
	return generate(sel->nont[0]) + generate(sel->nont[1]);
}

string gen_stats2(Node* sel) {
	if (sel->nont[0] == NULL) {
		return "";
	}
	return generate(sel->nont[0]) + generate(sel->nont[1]);
}

string gen_stat(Node* sel) {
	return generate(sel->nont[0]);
}

string gen_block(Node* sel) {
	return generate(sel->nont[1]);
}

string gen_in(Node* sel) {
	return "READ " + sel->token[0]->instance + "\n";
}

string gen_out(Node* sel) {
	string s = generate(sel->nont[0]);
	return s + "STORE _\nWRITE _\n";
}

string gen_if(Node* sel) {
	return "if"; //TODO
}

string gen_loop(Node* sel) {
	return "loop"; //TODO
}

string gen_assign(Node* sel) {
	string s = generate(sel->nont[0]);
	s += "STORE " + sel->token[0]->instance + "\n";
	return s;
}

string gen_relOp(Node* sel) {
	return "relOp"; //TODO
}
