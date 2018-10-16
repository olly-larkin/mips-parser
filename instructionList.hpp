#ifndef INSTRUCTIONLIST_HPP
#define INSTRUCTIONLIST_HPP

#include <iostream>
#include <vector>
#include <map>

uint32_t add(const std::vector<std::string>& argVec, const std::map<std::string, unsigned char>& regMap, const std::map<std::string, unsigned int>& labelMap);

#endif // INSTRUCTIONLIST_HPP