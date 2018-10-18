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
    {"div", {2, div_instr}},
    {"divu", {2, divu}},
    {"jr", {1, jr}},
    {"mfhi", {1, mfhi}},
    {"mflo", {1, mflo}},
    {"mult", {2, mult}},
    {"or", {3, or_instr}},
    {"sll", {3, sll}},
    {"sllv", {3, sllv}},
    {"slt", {3, slt}},
    {"sltu", {3, sltu}},
    {"sra", {3, sra}},
    {"srl", {3, srl}},
    {"srlv", {3, srlv}},
    {"sub", {3, sub}},
    {"subu", {3, subu}},
    {"xor", {3, xor_instr}},


    {"addi", {3, addi}},
    

    {"j", {1, j}},
    {"jal", {1, jal}}
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
            exitError("Invalid command \"" + inComm + "\" on instruction number " + std::to_string((count - 0x10000000)/4 + 1));
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
        uint32_t val = commMap[commVector[i][0]].fn(commVector[i], labelMap, i);
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
