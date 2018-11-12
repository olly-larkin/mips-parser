#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <vector>
#include <map>

typedef uint32_t (*commandFn)(std::vector<std::string>& argVec, int i);

struct numFn {
    int numArgs;
    commandFn fn;
};

bool validIntStr(std::string arg, int32_t& returnVal);
void vecParser(std::istream& inStream, std::vector< std::vector<std::string> >& commVector);
bool addVec(std::istream& inStream, std::vector< std::vector<std::string> >& commVector, unsigned int& count, std::string func);
void binGen(std::ofstream& outStream, std::vector< std::vector<std::string> >& commVector);
void fillMem(char memBlock[4], uint32_t num);
bool labelReturn(std::string str, int32_t& addr);

#endif  //PARSER_HPP