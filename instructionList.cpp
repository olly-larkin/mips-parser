#include <iostream>
#include <vector>
#include "instructionList.hpp"
#include <map>
#include <string>

std::map<std::string, unsigned char> regMap = {
    {"$zero", 0},
    {"$at", 1},
    {"$v0", 2},
    {"$v1", 3},
    {"$a0", 4},
    {"$a1", 5},
    {"$a2", 6},
    {"$a3", 7},
    {"$t0", 8},
    {"$t1", 9},
    {"$t2", 10},
    {"$t3", 11},
    {"$t4", 12},
    {"$t5", 13},
    {"$t6", 14},
    {"$t7", 15},
    {"$s0", 16},
    {"$s1", 17},
    {"$s2", 18},
    {"$s3", 19},
    {"$s4", 20},
    {"$s5", 21},
    {"$s6", 22},
    {"$s7", 23},
    {"$t8", 24},
    {"$t9", 25},
    {"$k0", 26},
    {"$k1", 27},
    {"$gp", 28},
    {"$sp", 29},
    {"$fp", 30},
    {"$ra", 31}
};

void exitError(std::string errMsg, int code) {
    std::cerr << errMsg << std::endl << std::endl;
    std::exit(code);
}

std::string giveStr(std::vector<std::string> strVec) {
    std::string returnStr;
    for(int i = 0; i < strVec.size(); ++i) {
        returnStr += strVec[i] + ' ';
    }
    return returnStr;
}

bool regCheck(std::vector<std::string>& argVec, const std::vector<int>& index) {
    for(int i = 0; i < index.size(); ++i) {
        if (argVec[index[i]].back() == ',')
            argVec[index[i]].pop_back();
        //if ()
    }
    return true;
}

uint32_t add(std::vector<std::string>& argVec, const std::map<std::string, unsigned int>& labelMap) {
    uint32_t returnNum = 32;

    std::vector<int> index = {1,2,3};
    if (!regCheck(argVec, index))
        exitError("Invalid command: " + giveStr(argVec));

    return returnNum;
}