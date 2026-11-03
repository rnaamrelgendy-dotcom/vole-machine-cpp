#ifndef UNTITLED6_CPU_H
#define UNTITLED6_CPU_H
#include <string>
#include "Register.h"
#include "Instruction.h"
#include "Memory.h"
#include "InputOutput.h"

class CPU {
private:
    int pc;
    std::string ir;
    Register registers [16];
public:
    CPU();
    ~CPU();

    std::string fetch(Memory& memory);
    Instruction decode();
    bool execute( const Instruction& instruction, Memory& memory ,InputOutput& io);
    int getPc() const;
    void setPc(int address);
    std::string getIR() const;
    Register* getRegisters();
    void reset();

};


#endif
