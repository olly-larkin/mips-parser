#include <iostream>
#include <vector>
#include "instructionList.hpp"
#include <map>
#include <string>

std::map<std::string, uint32_t> regMap = {
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
        if (regMap.find(argVec[index[i]]) == regMap.end())
            return false;
    }
    return true;
}

uint32_t add(std::vector<std::string>& argVec, std::map<std::string, unsigned int>& labelMap) {
    uint32_t returnNum = 32;
    std::vector<int> index = {1,2,3};
    if (!regCheck(argVec, index))
        exitError("Invalid register input: " + giveStr(argVec));
    returnNum = returnNum | ((regMap[argVec[1]] & 0x1F) << 11) | ((regMap[argVec[2]] & 0x1F) << 21) | ((regMap[argVec[3]] & 0x1F) << 16);
    return returnNum & 0x3FFF83F;
}

uint32_t j(std::vector<std::string>& argVec, std::map<std::string, unsigned int>& labelMap) {
    uint32_t returnNum = ((2 << 26) & 0xFC000000);
    uint32_t addr;
    if (labelMap.find(argVec[1]) == labelMap.end()) {
        std::size_t strCheck = 0;
        addr = std::stoi(argVec[1], &strCheck);
        if (strCheck != argVec[1].length())
            exitError("Invalid address: " + giveStr(argVec));
    } else
        addr = labelMap[argVec[1]];

    return returnNum | (((addr) >> 2) & 0x3FFFFFF);
}