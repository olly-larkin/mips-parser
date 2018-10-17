#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <vector>
#include <map>

typedef uint32_t (*commandFn)(std::vector<std::string>& argVec, std::map<std::string, unsigned int>& labelMap, int i);

struct numFn {
    int numArgs;
    commandFn fn;
};

void vecParser(std::istream& inStream, std::vector< std::vector<std::string> >& commVector);
void binGen(std::ofstream& outStream, std::vector< std::vector<std::string> >& commVector);
void fillMem(char memBlock[4], uint32_t num);

#endif  //PARSER_HPP