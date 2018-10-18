#ifndef INSTRUCTIONLIST_HPP
#define INSTRUCTIONLIST_HPP

#include <iostream>
#include <vector>
#include <map>

enum OP_TYPE {
    $s,
    $t,
    $d,
    shAmt,
    imm
};

void exitError(std::string errMsg, int code = 0);
std::string giveStr(std::vector<std::string> strVec);
bool regCheck(std::vector<std::string>& argVec, const std::vector<int>& index);
bool validIntStr(std::string arg, int32_t& returnVal);
uint32_t R_TYPE(std::vector<std::string>& argVec, const std::vector<OP_TYPE>& opcodes, int fn, int i);
uint32_t I_TYPE(std::vector<std::string>& argVec, const std::vector<OP_TYPE>& opcodes, int op, int i, bool branch = false);

//***************************** INSTRUCTIONS ***********************************

uint32_t add(std::vector<std::string>& argVec, int i);
uint32_t addu(std::vector<std::string>& argVec, int i);
uint32_t and_instr(std::vector<std::string>& argVec, int i);
uint32_t div_instr(std::vector<std::string>& argVec, int i);
uint32_t divu(std::vector<std::string>& argVec, int i);
uint32_t jr(std::vector<std::string>& argVec, int i);
uint32_t mfhi(std::vector<std::string>& argVec, int i);
uint32_t mflo(std::vector<std::string>& argVec, int i);
uint32_t mult(std::vector<std::string>& argVec, int i);
uint32_t multu(std::vector<std::string>& argVec, int i);
uint32_t or_instr(std::vector<std::string>& argVec, int i);
uint32_t sll(std::vector<std::string>& argVec, int i);
uint32_t sllv(std::vector<std::string>& argVec, int i);
uint32_t slt(std::vector<std::string>& argVec, int i);
uint32_t sltu(std::vector<std::string>& argVec, int i);
uint32_t sra(std::vector<std::string>& argVec, int i);
uint32_t srl(std::vector<std::string>& argVec, int i);
uint32_t srlv(std::vector<std::string>& argVec, int i);
uint32_t sub(std::vector<std::string>& argVec, int i);
uint32_t subu(std::vector<std::string>& argVec, int i);
uint32_t xor_instr(std::vector<std::string>& argVec, int i);

uint32_t addi(std::vector<std::string>& argVec, int i);
uint32_t addiu(std::vector<std::string>& argVec, int i);
uint32_t beq(std::vector<std::string>& argVec, int i);
uint32_t bgezal(std::vector<std::string>& argVec, int i);

uint32_t j(std::vector<std::string>& argVec, int i);
uint32_t jal(std::vector<std::string>& argVec, int i);

#endif // INSTRUCTIONLIST_HPP