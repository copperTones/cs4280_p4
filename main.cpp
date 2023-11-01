#include <iostream>
#include <fstream>
#include <string>
#include "scanner.h"
#include "parser.h"
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

	parser();
}
