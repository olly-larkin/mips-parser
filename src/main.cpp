#include <iostream>
#include <fstream>
#include "parser.hpp"
#include <vector>
#include <string>

std::string deleteFromEnd(std::string str, int num);

int main(int argc, char* argv[]) {

	std::vector< std::vector<std::string> > commVector;
	std::cout << std::endl;

	if (argc == 1) {
		vecParser(std::cin, commVector);
	} else {
		std::string inFileName = argv[1];
		std::ifstream inFile(inFileName);
		if (!inFile.is_open()) {
			std::cout << "Unable to open file." << std::endl << std::endl;
			std::exit(0);
		}
		vecParser(inFile, commVector);
		inFile.close();
	}

	std::cout << std::endl << "Commands passed successfully." << std::endl;

	std::string outFileName;
	if (argc == 1) {
		std::cout << "Please enter an output file name: ";
		std::cin >> outFileName;
	} else if (argc == 2) {
		outFileName = deleteFromEnd(argv[1], 4) + ".bin";
	} else {
		outFileName = argv[2];
	}
	std::ofstream outFile(outFileName, std::ios::binary);
	binGen(outFile, commVector);
	outFile.close();

	std::cout << "Output file generated: " << outFileName << std::endl << std::endl;
}

std::string deleteFromEnd(std::string str, int num) {
	for(int i = 0; i < num; ++i) {
		str.pop_back();
	}
	return str;
}