#include <iostream>
#include <fstream>
#include "parser.hpp"
#include <vector>

int main(int argc, char* argv[]) {
	std::cout << std::endl << "Please enter 'y' to use console entry (any character for file): ";
	std::string ans;
	std::cin >> ans;
	std::cout << std::endl;

	std::vector< std::vector<std::string> > commVector;

	if (ans == "y") {
		vecParser(std::cin, commVector);
	} else {
		std::ifstream inFile;
		while(!inFile.is_open()) {
			std::cout << "Please enter a name for your input file: " << std::endl;
			std::string inFileName;
			std::cin >> inFileName;
			inFile.open(inFileName);
			if (inFile.is_open())
				std::cout << "File opened successfully." << std::endl << std::endl;
			else
				std::cout << "File could not be opened." << std::endl;
		}
		vecParser(inFile, commVector);
		inFile.close();
	}

	std::cout << "Application read in successfully." << std::endl;

	std::cout << "Please enter an output file name: ";
	std::string outFileName;
	std::cin >> outFileName;
	std::ofstream outFile(outFileName, std::ios::binary | std::ios::out | std::ios::beg);
	binGen(outFile, commVector);

	std::cout << "Output file generated: " << outFileName << std::endl << std::endl;
}