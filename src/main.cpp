#include <iostream>
#include <fstream>
#include "parser.hpp"
#include <vector>
#include <string>

std::string deleteFromEnd(std::string str, int num);
std::string formatName(std::string str);

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
	if (argc == 2) {
		outFileName = formatName(argv[1]);
	} else if (argc == 3) {
		outFileName = argv[2];
	} else {
		std::cout << "Please enter an output file name: ";
		std::cin >> outFileName;
	}
	std::ofstream outFile(outFileName, std::ios::binary);
	if (!outFile.is_open()) {
		std::cout << "Unable to generate output file." << std::endl << std::endl;
		std::exit(0);
	}
	binGen(outFile, commVector);
	outFile.close();

	std::cout << "Output file generated: " << outFileName << std::endl << std::endl;
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