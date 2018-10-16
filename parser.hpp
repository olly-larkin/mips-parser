#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <vector>

typedef void (*commandFn)(std::vector<std::string>);

struct numFn {
    int numArgs;
    commandFn fn;
};

void vecParser(std::istream& inStream, std::vector< std::vector<std::string> > commVector);
void exitError(std::string errMsg, int code = 0);

#endif  //PARSER_HPP