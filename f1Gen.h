#ifndef F1_GEN_H
#define F1_GEN_H
#include <string>
#include "node.h"

string generate(Node*);
string gen_start(Node*);
string gen_vars(Node*);
string gen_varList(Node*);
string gen_exp(Node*);
string gen_exp2(Node*);
string gen_exp3(Node*);
string gen_exp4(Node*);
string gen_stats(Node*);
string gen_stats2(Node*);
string gen_stat(Node*);
string gen_block(Node*);
string gen_in(Node*);
string gen_out(Node*);
string gen_if(Node*);
string gen_loop(Node*);
string gen_assign(Node*);
string gen_relOp(Node*);
string label();
string genBR(string, string, bool = false);

#endif
