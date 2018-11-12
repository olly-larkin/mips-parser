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
    imm,
    regMem
};

void exitError(std::string errMsg, int code = 0);
std::string giveStr(std::vector<std::string> strVec);
bool regCheck(std::vector<std::string>& argVec, const std::vector<int>& index);
bool indRegCheck(std::string reg);
uint32_t R_TYPE(std::vector<std::string>& argVec, const std::vector<OP_TYPE>& opcodes, int fn, int pc);
uint32_t I_TYPE(std::vector<std::string>& argVec, const std::vector<OP_TYPE>& opcodes, int op, int pc, bool branch = false);
bool regMemSeperator(std::string str, int& offset, int& reg);

//***************************** INSTRUCTIONS ***********************************

uint32_t add(std::vector<std::string>& argVec, int i);
uint32_t addu(std::vector<std::string>& argVec, int i);
uint32_t and_instr(std::vector<std::string>& argVec, int i);
uint32_t div_instr(std::vector<std::string>& argVec, int i);
uint32_t divu(std::vector<std::string>& argVec, int i);
uint32_t jr(std::vector<std::string>& argVec, int i);
uint32_t jalr(std::vector<std::string>& argVec, int i);
uint32_t mfhi(std::vector<std::string>& argVec, int i);
uint32_t mflo(std::vector<std::string>& argVec, int i);
uint32_t mthi(std::vector<std::string>& argVec, int i);
uint32_t mtlo(std::vector<std::string>& argVec, int i);
uint32_t mult(std::vector<std::string>& argVec, int i);
uint32_t multu(std::vector<std::string>& argVec, int i);
uint32_t or_instr(std::vector<std::string>& argVec, int i);
uint32_t sll(std::vector<std::string>& argVec, int i);
uint32_t sllv(std::vector<std::string>& argVec, int i);
uint32_t slt(std::vector<std::string>& argVec, int i);
uint32_t sltu(std::vector<std::string>& argVec, int i);
uint32_t sra(std::vector<std::string>& argVec, int i);
uint32_t srav(std::vector<std::string>& argVec, int i);
uint32_t srl(std::vector<std::string>& argVec, int i);
uint32_t srlv(std::vector<std::string>& argVec, int i);
uint32_t sub(std::vector<std::string>& argVec, int i);
uint32_t subu(std::vector<std::string>& argVec, int i);
uint32_t xor_instr(std::vector<std::string>& argVec, int i);

uint32_t addi(std::vector<std::string>& argVec, int i);
uint32_t addiu(std::vector<std::string>& argVec, int i);
uint32_t andi(std::vector<std::string>& argVec, int i);
uint32_t beq(std::vector<std::string>& argVec, int i);
uint32_t bgezal(std::vector<std::string>& argVec, int i);
uint32_t bgez(std::vector<std::string>& argVec, int i);
uint32_t bgtz(std::vector<std::string>& argVec, int i);
uint32_t blez(std::vector<std::string>& argVec, int i);
uint32_t bltz(std::vector<std::string>& argVec, int i);
uint32_t bltzal(std::vector<std::string>& argVec, int i);
uint32_t bne(std::vector<std::string>& argVec, int i);
uint32_t ori(std::vector<std::string>& argVec, int i);
uint32_t slti(std::vector<std::string>& argVec, int i);
uint32_t sltiu(std::vector<std::string>& argVec, int i);
uint32_t xori(std::vector<std::string>& argVec, int i);
uint32_t lb(std::vector<std::string>& argVec, int i);
uint32_t lbu(std::vector<std::string>& argVec, int i);
uint32_t lh(std::vector<std::string>& argVec, int i);
uint32_t lhu(std::vector<std::string>& argVec, int i);
uint32_t lui(std::vector<std::string>& argVec, int i);
uint32_t lw(std::vector<std::string>& argVec, int i);
uint32_t lwl(std::vector<std::string>& argVec, int i);
uint32_t lwr(std::vector<std::string>& argVec, int i);
uint32_t sb(std::vector<std::string>& argVec, int i);
uint32_t sh(std::vector<std::string>& argVec, int i);
uint32_t sw(std::vector<std::string>& argVec, int i);

uint32_t j(std::vector<std::string>& argVec, int i);
uint32_t jal(std::vector<std::string>& argVec, int i);

uint32_t nop(std::vector<std::string>& argVec, int i);

#endif // INSTRUCTIONLIST_HPP