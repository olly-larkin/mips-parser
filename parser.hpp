#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <vector>
#include <map>

typedef uint32_t (*commandFn)(const std::vector<std::string>& argVec, const std::map<std::string, unsigned char>& regMap, const std::map<std::string, unsigned int>& labelMap);

struct numFn {
    int numArgs;
    commandFn fn;
};

void vecParser(std::istream& inStream, std::vector< std::vector<std::string> >& commVector);
void exitError(std::string errMsg, int code = 0);

#endif  //PARSER_HPP