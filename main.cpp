#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "scanner.h"
#include "parser.h"
#include "langTree.h"
#include "f1Gen.h"
using namespace std;

int main(int argc, char* argv[]) {
	string fname = "a";
	ifstream inpf;
	if (argc > 2) {
		cout << "Too many arguments\n";
		return 1;
	} else if (argc == 2) {
		fname =  argv[1];
		inpf.open((fname + ".f1").c_str());
		if (!inpf) {
			cout << "Could not open file\n";
			return 1;
		}
		scanFile(&inpf);
	} else {
		scanFile(&cin);
	}

	Node* tree;
	try {
		tree = parser();
		decorate(tree);
	} catch (const runtime_error& e) {
		cout << e.what() << "\n";
		return -1;
	}
	string s = generate(tree);
	fname += ".asm";
	ofstream outf(fname.c_str());
	outf << s;
	outf.close();
}
