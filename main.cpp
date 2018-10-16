#include <iostream>
#include <fstream>
#include "parser.hpp"
#include <vector>

int main(int argc, char* argv[]) {
	std::cout << std::endl << "Please enter 'y' to use console entry (any character for file): ";
	std::string ans;
	std::cin >> ans;

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

	for(int i = 0; i < commVector.size(); ++i) {
		for(int j = 0; j < commVector[i].size(); ++j) {
			std::cout << commVector[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}