#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "scanner.h"
#include "parser.h"
#include "langTree.h"
using namespace std;

int main(int argc, char* argv[]) {
	ifstream inpf;
	if (argc > 2) {
		cout << "Too many arguments\n";
		return 1;
	} else if (argc == 2) {
		string fname(argv[1]);
		fname += ".f1";
		inpf.open(fname.c_str());
		if (!inpf) {
			cout << "Could not open file\n";
			return 1;
		}
		scanFile(&inpf);
	} else {
		scanFile(&cin);
	}

	try {
		Node* tree = parser();
		decorate(tree);
	} catch (const runtime_error& e) {
		cout << e.what() << "\n";
		return -1;
	}
}
