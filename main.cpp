#include <iostream>
#include <fstream>
#include "parser.hpp"

int main(int argc, char* argv[]) {
	std::cout << std::endl << "Please enter 'y' to use console entry (any character for file): ";
	std::string ans;
	std::cin >> ans;

	if (ans == "y") {
		// CALL PARSING FUNCTION
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
		// CALL PARSING FUNCTION
		inFile.close();
	}

	std::cout << "Application read in successfully." << std::endl;
}