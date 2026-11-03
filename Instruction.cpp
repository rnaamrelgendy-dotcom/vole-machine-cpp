#include "Instruction.h"
#include <cctype>
using namespace std;

Instruction::Instruction() {
    opcode="";
    operand1="";
    operand2="";
    operand3="";
    rawInstruction="";
}

Instruction::Instruction(const std::string &raw) {
    parse(raw);
}

bool Instruction::parse(const std::string& raw) {
    if (raw.size()!=4) return false;
    rawInstruction=raw;
    for (char& c : rawInstruction) c=toupper(c);
    opcode=std::string(1,rawInstruction[0]);
    operand1=std::string(1,rawInstruction[1]);
    operand2=std::string(1,rawInstruction[2]);
    operand3=std::string(1,rawInstruction[3]);
    return validate();
}


bool Instruction::validate() {
    if (rawInstruction.size()!=4) return false;
    for (char c : rawInstruction) {
        if (!isxdigit(c)) return false;//0-9,A-Z
    }
    int op = stoi(opcode, nullptr, 16);
    if (op < 1 || op > 12) {
        return false;
    }
    if (op == 4 && operand1 != "0") return false;
    if (op == 12 && operand1 + operand2 + operand3 != "000") return false;

    return true;

}


std::string Instruction::getOpcode() const{
    return opcode;
}

std::string Instruction::getOperand1() const {
    return operand1;
}

std::string Instruction::getOperand2() const{
    return operand2;
}

std::string Instruction::getOperand3() const{
    return operand3;
}

Instruction::~Instruction() {}

