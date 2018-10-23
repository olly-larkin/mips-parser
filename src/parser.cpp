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
    {"mthi", {1, mthi}},
    {"mtlo", {1, mtlo}},
    {"mult", {2, mult}},
    {"multu", {2, multu}},
    {"or", {3, or_instr}},
    {"sll", {3, sll}},
    {"sllv", {3, sllv}},
    {"slt", {3, slt}},
    {"sltu", {3, sltu}},
    {"sra", {3, sra}},
    {"srav", {3, srav}},
    {"srl", {3, srl}},
    {"srlv", {3, srlv}},
    {"sub", {3, sub}},
    {"subu", {3, subu}},
    {"xor", {3, xor_instr}},


    {"addi", {3, addi}},
    {"addiu", {3,addiu}},
    {"andi", {3,andi}},
    {"beq", {3, beq}},
    {"bgezal", {2, bgezal}},
    {"bgez", {2,bgez}},
    {"bgtz", {2, bgtz}},
    {"blez", {2, blez}},
    {"bltz", {2, bltz}},
    {"bltzal", {2,bltzal}},
    {"bne", {3, bne}},
    {"ori", {3,ori}},
    {"slti", {3,slti}},
    {"sltiu", {3,sltiu}},
    {"xori", {3,xori}},
    {"lb", {2, lb}},
    {"lbu", {2, lbu}},
    {"lh", {2, lh}},
    {"lhu", {2, lhu}},
    {"lui", {2, lui}},
    {"lw", {2, lw}},
    {"lwl", {2, lwl}},
    {"lwr", {2, lwr}},
    {"sb", {2, sb}},
    {"sh", {2, sh}},
    {"sw", {2, sw}},


    {"j", {1, j}},
    {"jal", {1, jal}},

    {"nop", {0, nop}}
};

std::map<std::string, unsigned int> labelMap = {
    {"ADDR_NULL", 0x0},
    {"ADDR_INSTR", 0x10000000},
    {"ADDR_DATA", 0x20000000},
    {"ADDR_GETC", 0x30000000},
    {"ADDR_PUTC", 0x30000004}
};

void vecParser(std::istream& inStream, std::vector< std::vector<std::string> >& commVector) {
    std::string inComm;
    unsigned int count = 0x10000000;
    
    std::vector<std::string> inVec;

    while(1) {
        if (!(inStream >> inComm) || inComm == "exit")
            break;
        else if (inComm.back() == ':') {
            inComm.pop_back();
            labelMap[inComm] = count;
        } else if (commMap.find(inComm) == commMap.end())
            exitError("Invalid command \"" + inComm + "\" on instruction number " + std::to_string((count - 0x10000000)/4 + 1));
        else {
            inVec.clear();
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
        uint32_t val = commMap[commVector[i][0]].fn(commVector[i], i);
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

bool labelReturn(std::string str, int32_t& addr) {
    if (labelMap.find(str) == labelMap.end())
        return false;
    addr = labelMap[str];
    return true;
}
