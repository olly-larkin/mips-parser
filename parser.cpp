#include <iostream>
#include "parser.hpp"
#include <fstream>
#include <vector>
#include <map>
#include "instructionList.hpp"
#include <string>

std::map<std::string, numFn> commMap = {
    {"add", {3, add}},
    {"addu", {3, addu}},
    {"and", {3, and_instr}},
    {"jr", {1, jr}},
    {"j", {1, j}}
};

std::map<std::string, unsigned int> labelMap;

void vecParser(std::istream& inStream, std::vector< std::vector<std::string> >& commVector) {
    std::string inComm;
    unsigned int count = 0x10000000;

    while(inComm != "terminate") {
        inStream >> inComm;
        if (inComm == "terminate")
            break;
        else if (inComm.back() == ':') {
            inComm.pop_back();
            labelMap[inComm] = count;
        } else if (commMap.find(inComm) == commMap.end())
            exitError("Invalid command: " + inComm);
        else {
            std::vector<std::string> inVec;
            inVec.push_back(inComm);
            for(int i = 0; i < commMap[inComm].numArgs; ++i) {
                std::string arg;
                inStream >> arg;
                inVec.push_back(arg);
            }
            commVector.push_back(inVec);
            count += 4;
        }
    }
}

void binGen(std::ofstream& outStream, std::vector< std::vector<std::string> >& commVector) {
    for(int i = 0; i < commVector.size(); ++i) {
        char memBlock[4];
        uint32_t val = commMap[commVector[i][0]].fn(commVector[i], labelMap);
        fillMem(memBlock, val);
        outStream.write(memBlock, 4);
    }
}

void fillMem(char memBlock[4], uint32_t num) {
    memBlock[0] = ((num >> 24) & 0xFF);
    memBlock[1] = ((num >> 16) & 0xFF);
    memBlock[2] = ((num >> 8) & 0xFF);
    memBlock[3] = (num & 0xFF);
}
