#include "langTree.h"
#include "f1Gen.h"

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
	string a = label(), b = label();
	string s = generate(sel->nont[0]);
	s += "PUSH\n"
	     "STACKW 0\n";
	s += generate(sel->nont[2]);
	s += "STORE _\n"
	     "STACKR 0\n"
	     "SUB _\n"
	     "POP\n";
	s += genBR(sel->nont[1]->token[0]->instance, b);
	s += "BR " + a + "\n";
	s += b + ": NOOP\n";
	s += generate(sel->nont[3]);
	s += a + ": NOOP\n";
	return s;
}

string gen_loop(Node* sel) {
	string a = label(), b = label();
	string s = "PUSH\n"
	           + a + ": NOOP\n";
	s += generate(sel->nont[0]);
	s += "STACKW 0\n";
	s += generate(sel->nont[2]);
	s += "STORE _\n"
	     "STACKR 0\n"
	     "SUB _\n";
	s += genBR(sel->nont[1]->token[0]->instance, b, true);
	s += generate(sel->nont[3]);
	s += "BR " + a + "\n"
	     + b + ": NOOP\n"
	     "POP\n";
	return s;
}

string gen_assign(Node* sel) {
	string s = generate(sel->nont[0]);
	s += "STORE " + sel->token[0]->instance + "\n";
	return s;
}

string gen_relOp(Node* sel) {
	return "generator error!\n";
}

string label() {
	static int labelId = 0;
	return "_" + to_string(labelId++);
}

string genBR(string inst, string to, bool swap) {
	int type;
	if (inst == "<=") {
		type = 3;
	} else if (inst == ">=") {
		type = 5;
	} else if (inst == "<") {
		type = 4;
	} else if (inst == ">") {
		type = 2;
	} else if (inst == "=") {
		type = 0;
	} else if (inst == "~") {
		type = 1;
	} else {
		return "generator error!\n";
	}

	type ^= swap; // even-odd if swap
	string a, s;
	switch (type) {
	case 0:
		return "BRZERO " + to + "\n";
	case 1:
		a = label();
		s = "BRZERO " + a + "\n";
		s += "BR " + to + "\n";
		s += a + ": NOOP\n";
		return s;
	case 2:
		return "BRPOS " + to + "\n";
	case 3:
		return "BRZNEG " + to + "\n";
	case 4:
		return "BRNEG " + to + "\n";
	case 5:
		return "BRZPOS " + to + "\n";
	default:
		return "generator error!\n";
	}
}
