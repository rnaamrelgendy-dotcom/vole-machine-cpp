#pragma once
#include <string>



class Instruction {
private:
    std::string opcode;
    std::string operand1;
    std::string operand2;
    std::string operand3;
    std::string rawInstruction;


public:
    Instruction();
    Instruction(const std::string& raw);
    bool parse(const std::string& raw);

    bool validate();
    std::string getOpcode() const;
    std::string getOperand1() const;
    std::string getOperand2() const;
    std::string getOperand3() const;
    ~Instruction() ;

};
