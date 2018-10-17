#ifndef INSTRUCTIONLIST_HPP
#define INSTRUCTIONLIST_HPP

#include <iostream>
#include <vector>
#include <map>

void exitError(std::string errMsg, int code = 0);
std::string giveStr(std::vector<std::string> strVec);
bool regCheck(std::vector<std::string>& argVec, const std::vector<int>& index);

uint32_t add(std::vector<std::string>& argVec, std::map<std::string, unsigned int>& labelMap);
uint32_t j(std::vector<std::string>& argVec, std::map<std::string, unsigned int>& labelMap);

#endif // INSTRUCTIONLIST_HPP