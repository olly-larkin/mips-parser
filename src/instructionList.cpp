#include <iostream>
#include <vector>
#include "instructionList.hpp"
#include <map>
#include <string>
#include "parser.hpp"

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
    {"$ra", 31},
    {"$0", 0},
    {"$1", 1},
    {"$2", 2},
    {"$3", 3},
    {"$4", 4},
    {"$5", 5},
    {"$6", 6},
    {"$7", 7},
    {"$8", 8},
    {"$9", 9},
    {"$10", 10},
    {"$11", 11},
    {"$12", 12},
    {"$13", 13},
    {"$14", 14},
    {"$15", 15},
    {"$16", 16},
    {"$17", 17},
    {"$18", 18},
    {"$19", 19},
    {"$20", 20},
    {"$21", 21},
    {"$22", 22},
    {"$23", 23},
    {"$24", 24},
    {"$25", 25},
    {"$26", 26},
    {"$27", 27},
    {"$28", 28},
    {"$29", 29},
    {"$30", 30},
    {"$31", 31}
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

bool indRegCheck(std::string reg) {
    if (reg.back() == ',')
        reg.pop_back();
    return (regMap.find(reg) != regMap.end());
}

uint32_t R_TYPE(std::vector<std::string>& argVec, const std::vector<OP_TYPE>& opcodes, int fn, int pc) {
    uint32_t returnNum = fn;
    std::vector<int> index;
    for(int i = 0; i < opcodes.size(); ++i) {
        if (opcodes[i] == $s || opcodes[i] == $t || opcodes[i] == $d)
            index.push_back(i+1);
    }
    if (!regCheck(argVec, index))
        exitError("Invalid register input \"" + giveStr(argVec) + "\" on instruction number " + std::to_string(pc+1), 5);
    for(int i = 0; i < opcodes.size(); ++i) {
        switch(opcodes[i]) {
            case shAmt:
                int32_t shAmtNum;
                if (!validIntStr(argVec[i+1], shAmtNum))
                    exitError("Invalid instruction argument \"" + giveStr(argVec) + "\" on instruction number " + std::to_string(pc+1), 5);
                returnNum = returnNum | ((shAmtNum & 0x1F) << 6);
                break;
            case $d:
                returnNum = returnNum | ((regMap[argVec[i+1]] & 0x1F) << 11);
                break;
            case $t:
                returnNum = returnNum | ((regMap[argVec[i+1]] & 0x1F) << 16);
                break;
            case $s:
                returnNum = returnNum | ((regMap[argVec[i+1]] & 0x1F) << 21);
                break;
            default:
                break;
        }
    }
    return returnNum;
}

uint32_t I_TYPE(std::vector<std::string>& argVec, const std::vector<OP_TYPE>& opcodes, int op, int pc, bool branch) {
    uint32_t returnNum = (op << 26) & 0xFC000000;
    int32_t immediate = 0;
    std::vector<int> index;
    for(int i = 0; i < opcodes.size(); ++i) {
        if (opcodes[i] == $s || opcodes[i] == $t || opcodes[i] == $d)
            index.push_back(i+1);
    }
    if (!regCheck(argVec, index))
        exitError("Invalid register input \"" + giveStr(argVec) + "\" on instruction number " + std::to_string(pc+1), 5);
    for(int i = 0; i < opcodes.size(); ++i) {
        switch(opcodes[i]) {
            case imm:
                if (branch && labelReturn(argVec[i+1], immediate)) {
                    immediate = immediate - ((pc+1)*4 + 0x10000000);
                    immediate = immediate >> 2;

                } else {
                    if (!validIntStr(argVec[i+1], immediate))
                        exitError("Invalid instruction argument \"" + giveStr(argVec) + "\" on instruction number " + std::to_string(pc+1), 5);
                }
                returnNum = returnNum | (immediate & 0xFFFF);
                break;
            case $t:
                returnNum = returnNum | ((regMap[argVec[i+1]] & 0x1F) << 16);
                break;
            case $s:
                returnNum = returnNum | ((regMap[argVec[i+1]] & 0x1F) << 21);
                break;
            case regMem:
                int offset, reg;
                if (!regMemSeperator(argVec[i+1], offset, reg))
                    exitError("Invalid instruction argument \"" + giveStr(argVec) + "\" on instruction number " + std::to_string(i+1), 5);
                returnNum = returnNum | (offset & 0xFFFF) | ((reg & 0x1F) << 21);
                break;
            default:
                break;
        }
    }
    return returnNum;
}

bool regMemSeperator(std::string str, int& offset, int& reg) {
    std::size_t index;
    offset = std::stoi(str, &index, 0);
    if (index == 0 || str[index] != '(')
        return false;
    str.pop_back();
    std::string regStr;
    for(int i = index+1; i < str.size(); ++i)
        regStr += str[i];
    if (regMap.find(regStr) == regMap.end())
        return false;
    reg = regMap[regStr];
    return true;
}

//***************************** INSTRUCTIONS ***********************************

//*********************************** R TYPE ************************************

uint32_t add(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$d, $s, $t};
    return R_TYPE(argVec, opcodes, 32, i);
}

uint32_t addu(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$d, $s, $t};
    return R_TYPE(argVec, opcodes, 33, i);
}

uint32_t and_instr(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$d, $s, $t};
    return R_TYPE(argVec, opcodes, 36, i);
}

uint32_t div_instr(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$s, $t};
    return R_TYPE(argVec, opcodes, 26, i);
}

uint32_t divu(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$s, $t};
    return R_TYPE(argVec, opcodes, 27, i);
}

uint32_t jr(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$s};
    return R_TYPE(argVec, opcodes, 8, i);
}

uint32_t jalr(std::vector<std::string>& argVec, int i){
    std::vector<OP_TYPE> opcodes = {$d, $s};
    return R_TYPE(argVec, opcodes, 9, i);
}

uint32_t mfhi(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$d};
    return R_TYPE(argVec, opcodes, 16, i);
}

uint32_t mflo(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$d};
    return R_TYPE(argVec, opcodes, 18, i);
}

uint32_t mthi(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$s};
    return R_TYPE(argVec, opcodes, 17, i);
}

uint32_t mtlo(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$s};
    return R_TYPE(argVec, opcodes, 19, i);
}

uint32_t mult(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$s, $t};
    return R_TYPE(argVec, opcodes, 24, i);
}

uint32_t multu(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$s, $t};
    return R_TYPE(argVec, opcodes, 25, i);
}

uint32_t or_instr(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$d, $s, $t};
    return R_TYPE(argVec, opcodes, 37, i);
}

uint32_t sll(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$d, $t, shAmt};
    return R_TYPE(argVec, opcodes, 0, i);
}

uint32_t sllv(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$d, $t, $s};
    return R_TYPE(argVec, opcodes, 4, i);
}

uint32_t slt(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$d, $s, $t};
    return R_TYPE(argVec, opcodes, 42, i);
}

uint32_t sltu(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$d, $s, $t};
    return R_TYPE(argVec, opcodes, 43, i);
}

uint32_t sra(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$d, $t, shAmt};
    return R_TYPE(argVec, opcodes, 3, i);
}

uint32_t srav(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$d, $t, $s};
    return R_TYPE(argVec, opcodes, 7, i);
}

uint32_t srl(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$d, $t, shAmt};
    return R_TYPE(argVec, opcodes, 2, i);
}

uint32_t srlv(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$d, $t, $s};
    return R_TYPE(argVec, opcodes, 6, i);
}

uint32_t sub(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$d, $s, $t};
    return R_TYPE(argVec, opcodes, 34, i);
}

uint32_t subu(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$d, $s, $t};
    return R_TYPE(argVec, opcodes, 35, i);
}

uint32_t xor_instr(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$d, $s, $t};
    return R_TYPE(argVec, opcodes, 38, i);
}

//*********************************** I TYPE ************************************

uint32_t addi(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$t, $s, imm};
    return I_TYPE(argVec, opcodes, 8, i);
}

uint32_t addiu(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$t, $s, imm};
    return I_TYPE(argVec, opcodes, 9, i);
}

uint32_t andi(std::vector<std::string>& argVec, int i){
    std::vector<OP_TYPE> opcodes = {$t, $s, imm};
    return I_TYPE(argVec, opcodes, 12, i);
}

uint32_t beq(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$s, $t, imm};
    return I_TYPE(argVec, opcodes, 4, i, true);
}

uint32_t bgezal(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$s, imm};
    return I_TYPE(argVec, opcodes, 1, i, true) | (17 << 16);
}

uint32_t bgez(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$s, imm};
    return I_TYPE(argVec, opcodes, 1, i, true) | (1 << 16);
}

uint32_t bgtz(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$s, imm};
    return I_TYPE(argVec, opcodes, 7, i, true);
}

uint32_t blez(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$s, imm};
    return I_TYPE(argVec, opcodes, 6, i, true);
}

uint32_t bltz(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$s, imm};
    return I_TYPE(argVec, opcodes, 1, i, true);
}

uint32_t bltzal(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$s, imm};
    return I_TYPE(argVec, opcodes, 1, i, true) | (16 << 16);
}

uint32_t bne(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$s, $t, imm};
    return I_TYPE(argVec, opcodes, 5, i, true);
}

uint32_t ori(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$t, $s, imm};
    return I_TYPE(argVec, opcodes, 13, i);
}

uint32_t slti(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$t, $s, imm};
    return I_TYPE(argVec, opcodes, 10, i);
}

uint32_t sltiu(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$t, $s, imm};
    return I_TYPE(argVec, opcodes, 11, i);
}

uint32_t xori(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$t, $s, imm};
    return I_TYPE(argVec, opcodes, 14, i);
}

uint32_t lb(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$t, regMem};
    return I_TYPE(argVec, opcodes, 32, i);
}

uint32_t lbu(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$t, regMem};
    return I_TYPE(argVec, opcodes, 36, i);
}

uint32_t lh(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$t, regMem};
    return I_TYPE(argVec, opcodes, 33, i);
}

uint32_t lhu(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$t, regMem};
    return I_TYPE(argVec, opcodes, 37, i);
}

uint32_t lui(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$t, imm};
    return I_TYPE(argVec, opcodes, 15, i);
}

uint32_t lw(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$t, regMem};
    return I_TYPE(argVec, opcodes, 35, i);
}

uint32_t lwl(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$t, regMem};
    return I_TYPE(argVec, opcodes, 34, i);
}

uint32_t lwr(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$t, regMem};
    return I_TYPE(argVec, opcodes, 38, i);
}

uint32_t sb(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$t, regMem};
    return I_TYPE(argVec, opcodes, 40, i);
}

uint32_t sh(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$t, regMem};
    return I_TYPE(argVec, opcodes, 41, i);
}

uint32_t sw(std::vector<std::string>& argVec, int i) {
    std::vector<OP_TYPE> opcodes = {$t, regMem};
    return I_TYPE(argVec, opcodes, 43, i);
}

//*********************************** J TYPE ************************************

uint32_t j(std::vector<std::string>& argVec, int i) {
    uint32_t returnNum = ((2 << 26) & 0xFC000000);
    int32_t addr;
    if(!labelReturn(argVec[1], addr)) {
        if (!validIntStr(argVec[1], addr))
            exitError("Invalid address \"" + giveStr(argVec) + "\" on instruction number " + std::to_string(i+1), 5);
    }
    return returnNum | (((addr) >> 2) & 0x3FFFFFF);
}

uint32_t jal(std::vector<std::string>& argVec, int i) {
    uint32_t returnNum = ((3 << 26) & 0xFC000000);
    int32_t addr;
    if(!labelReturn(argVec[1], addr)) {
        if (!validIntStr(argVec[1], addr))
            exitError("Invalid address \"" + giveStr(argVec) + "\" on instruction number " + std::to_string(i+1), 5);
    }
    return returnNum | (((addr) >> 2) & 0x3FFFFFF);
}

//*********************************** NOP **************************************

uint32_t nop(std::vector<std::string>& argVec, int i) {
    return 0;
}