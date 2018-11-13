#include <iostream>
#include <fstream>
#include "parser.hpp"
#include <vector>
#include <string>

std::string formatName(std::string str);

int main(int argc, char* argv[]) {

	std::vector< std::vector<std::string> > commVector;
	std::cerr << std::endl;

	if (argc == 1) {
		std::cerr << "------------------------------------- " << std::endl;
		std::cerr << "*********** CONSOLE INPUT *********** " << std::endl;
		std::cerr << "------------------------------------- " << std::endl << std::endl;
		vecParser(std::cin, commVector);
	} else {
		std::string inFileName = argv[1];
		std::ifstream inFile(inFileName);
		if (!inFile.is_open()) {
			std::cerr << "Unable to open file." << std::endl << std::endl;
			std::exit(0);
		}
		vecParser(inFile, commVector);
		inFile.close();
	}

	std::cerr << std::endl << "Commands passed successfully." << std::endl;

	std::string outFileName;
	
	if (argc == 1) {
		std::cerr << "Please enter an output file name: ";
		std::cin >> outFileName;
	} else {
		outFileName = formatName(argv[1]);
		if (argc == 3) {
			std::string str = argv[2];
			if (str.back() == '#') {
				str.pop_back();
				outFileName = str + outFileName;
			} else
				outFileName = argv[2];
		}
	}

	std::ofstream outFile(outFileName, std::ios::binary);
	if (!outFile.is_open()) {
		std::cerr << "Unable to generate output file." << std::endl << std::endl;
		std::exit(5);
	}
	binGen(outFile, commVector);
	outFile.close();

	std::cerr << "Output file generated: " << outFileName << std::endl << std::endl;
}

std::string formatName(std::string str) {
	std::size_t dotIndex = str.size();
	std::size_t slashIndex = -1;
	for(int i = str.size()-1; i >= 0; --i) {
		if (str[i] == '.' && dotIndex == str.size())
			dotIndex = i;
		if (str[i] == '/' && slashIndex == -1)
			slashIndex = i;
	}
	return str.substr(slashIndex+1, (dotIndex - slashIndex - 1)) + ".bin";
}