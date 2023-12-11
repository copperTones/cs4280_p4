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
	return "generator error!\n";
}

string gen_varList(Node* sel) {
	return "generator error!\n";
}

string gen_exp(Node* sel) {
	string s = generate(sel->nont[0]);
	if (sel->token[0] != NULL) {
		s += "PUSH\nSTACKW 0\n";
		s += generate(sel->nont[1]);
		s += "STORE _\nSTACKR 0\n";
		if (sel->token[0]->instance == "+") {
			s += "ADD";
		} else {
			s += "SUB";
		}
		s += " _\nPOP\n";
	}
	return s;
}

string gen_exp2(Node* sel) {
	string s = generate(sel->nont[0]);
	if (sel->token[0] != NULL) {
		s += "PUSH\nSTACKW 0\n";
		s += generate(sel->nont[1]);
		s += "STORE _\nSTACKR 0\nMULT _\nPOP\n";
	}
	return s;
}

string gen_exp3(Node* sel) {
	string s = generate(sel->nont[0]);
	if (sel->token[0] != NULL) {
		if (sel->token[0]->instance == "/") {
			s += "PUSH\nSTACKW 0\n";
			s += generate(sel->nont[1]);
			s += "STORE _\nSTACKR 0\nDIV _\nPOP\n";
		} else {
			s += "MULT -1\n";
		}
	}
	return s;
}

string gen_exp4(Node* sel) {
	if (sel->nont[0] != NULL) {
		return generate(sel->nont[0]);
	} else {
		return "LOAD " + sel->token[0]->instance + "\n";
	}
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
	labelId++;
	string s = generate(sel->nont[0]);
	s += "PUSH\n"
	     "STACKW 0\n";
	s += generate(sel->nont[2]);
	s += "STORE _\n"
	     "STACKR 0\n"
	     "SUB _\n"
	     "POP\n";
	s += generate(sel->nont[1]);
	s += "BR _a" + to_string(labelId) + "\n";
	s += "_b" + to_string(labelId) + ": NOOP\n";
	s += generate(sel->nont[3]);
	s += "_a" + to_string(labelId) + ": NOOP\n";
	labelId--;
	return s;
}

string gen_loop(Node* sel) {
	labelId++;
	string s = "PUSH\n"
	           "_a" + to_string(labelId) + ": NOOP\n";
	s += generate(sel->nont[0]);
	s += "STACKW 0\n";
	s += generate(sel->nont[2]);
	s += "STORE _\n"
	     "STACKR 0\n"
	     "SUB _\n";
	s += generate(sel->nont[1]);
	s += generate(sel->nont[3]);
	s += "BR _a" + to_string(labelId) + "\n"
	     "_b" + to_string(labelId) + ": NOOP\n"
	     "POP\n";
	labelId--;
	return s;
}

string gen_assign(Node* sel) {
	string s = generate(sel->nont[0]);
	s += "STORE " + sel->token[0]->instance + "\n";
	return s;
}

string gen_relOp(Node* sel) {
	string i = sel->token[0]->instance;
	if (i == "<=") {
		return "BRPOS _b" + to_string(labelId) + "\n";
	} else if (i == ">=") {
		return "BRNEG _b" + to_string(labelId) + "\n";
	} else if (i == "<") {
		return "BRZPOS _b" + to_string(labelId) + "\n";
	} else if (i == ">") {
		return "BRZNEG _b" + to_string(labelId) + "\n";
	} else if (i == "=") {
		return "BRZERO _b" + to_string(labelId) + "\n";
	} else if (i == "~") {
		string s = "BRZERO _c" + to_string(labelId) + "\n";
		s += "BR _b" + to_string(labelId) + "\n";
		s += "_c" + to_string(labelId) + ": NOOP\n";
		return s;
	} else {
		return "generator error!\n";
	}
}
