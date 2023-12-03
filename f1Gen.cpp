#include "langTree.h"
#include "f1Gen.h"

string generate(Node* sel) {
	return sel->type(sel);
}

string gen_start(Node* sel) {
	string s = "STOP";
	for (auto &v: vars) {
		s += "\n" + v.first;
		s += " " + v.second.value;
	}
	return s;
}

string gen_vars(Node* sel) {
	return "";
}

string gen_varList(Node* sel) {
	return "";
}

string gen_exp(Node* sel) {
	return "";
}

string gen_exp2(Node* sel) {
	return "";
}

string gen_exp3(Node* sel) {
	return "";
}

string gen_exp4(Node* sel) {
	return "";
}

string gen_stats(Node* sel) {
	return "";
}

string gen_stats2(Node* sel) {
	return "";
}

string gen_stat(Node* sel) {
	return "";
}

string gen_block(Node* sel) {
	return "";
}

string gen_in(Node* sel) {
	return "";
}

string gen_out(Node* sel) {
	return "";
}

string gen_if(Node* sel) {
	return "";
}

string gen_loop(Node* sel) {
	return "";
}

string gen_assign(Node* sel) {
	return "";
}

string gen_relOp(Node* sel) {
	return "";
}
