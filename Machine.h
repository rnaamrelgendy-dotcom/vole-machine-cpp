#pragma once
#include <string>
#include "CPU.h"
#include "Register.h"
#include "Loader.h"
#include "Memory.h"


class Machine {
private:
    CPU cpu;
    Memory memory;
    Loader loader;
    InputOutput io;
    bool running;
public:
    Machine();
    bool loadProgram(std::string filename);
    void run();
    bool step();
    void reset();
    void displayStats();
    void displayRegisters();
    void displayMemory();

    InputOutput& getIO()     { return io; }
    Memory&      getMemory() { return memory; }
    CPU&         getCPU()    { return cpu; }
};