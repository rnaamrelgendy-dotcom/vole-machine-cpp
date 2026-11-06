#include "Machine.h"
#include<string>
#include <iostream>
#include <ostream>
#include "CPU.h"
#include "Instruction.h"
#include "Memory.h"
#include "Register.h"
#include "Loader.h"



Machine::Machine() {
    running = false;
}


bool Machine::loadProgram(std::string filename) {
    reset();
    int startAddress = 0;
    if (!loader.loadprogram(filename, startAddress, memory)) {
        return false;
    }

    cpu.setPc(startAddress);
    return true;
}

void Machine::run() {
    running = true;
    while (running) {
        if (!step()) {
            running = false;
        }
    }
}

bool Machine::step() {
    cpu.fetch(memory);

    Instruction instruction = cpu.decode();

    bool valid = cpu.execute(instruction, memory, io);

    return valid;
}

void Machine::reset() {
    running = false;
    cpu.reset();
    memory.clear();

}

void Machine::displayStats() {
    if (running) {
        cout<<"Machine running\n";
    }else {
        cout<<"Machine not running\n";
    }
    cout<<"Program Counter : "<<cpu.getPc()<<"\n";
    cout<<"Instruction Register : "<<cpu.getIR()<<"\n";
}

void Machine::displayRegisters(){
    Register* registers = cpu.getRegisters();
    for (int i = 0; i < 16; i++) {
        cout << "R" << i << ": "
             << registers[i].getValue() << "\n";
    }
}