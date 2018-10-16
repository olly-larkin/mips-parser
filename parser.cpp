#include <iostream>
#include "parser.hpp"
#include <fstream>
#include <vector>
#include <map>
#include "instructionList.hpp"

std::map<std::string, numFn> commMap = {
    {"add", {3, add}}
};

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
            exitError("Invalid command.");
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

void exitError(std::string errMsg, int code) {
    std::cerr << errMsg << std::endl << std::endl;
    std::exit(code);
}
