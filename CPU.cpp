#include "CPU.h"
#include <cmath>
#include <sstream>
#include <iomanip>

CPU::CPU():pc(0),ir(""){}
CPU::~CPU(){}

int CPU::getPc() const {
    return pc;
}

void CPU::setPc(int address) {
    pc = address;
}

std::string CPU::getIR() const {
    return ir;
}

Register* CPU::getRegisters() {
    return registers;
}

void CPU::reset() {
    pc = 0;
    ir="";
    for (int i=0;i<16;i++) {
        registers[i].clear();
    }
}

std::string CPU::fetch(Memory& memory) {
    ir=memory.read(pc)+memory.read(pc+1);
    pc+=2;
    return ir;
}

Instruction CPU::decode() {
    Instruction inst;
    inst.parse(ir);
    return inst;
}

static int hexToInt(const std::string& s) {//for register&memory
    return std::stoi(s,nullptr,16);
}

static std::string intToHex(int n) {
    std::stringstream s;
    s<<std::uppercase <<std::hex<<std::setw(2)<<std::setfill('0')<<(n&0xFF);
    return s.str();

}

static double byteToFloat(int b) {
    int s = (b >> 7) & 1;
    int e = (b >> 4) & 7;
    int m = b & 15;
    double v = (m / 16.0) * std::pow(2, e - 4);
    return s ? -v : v;
}


static int floatToByte(double v) {
    if (v == 0) return 0;
    int s = v < 0;
    v = std::fabs(v);
    int e = 4;
    while (v >= 1.0 && e < 7) { v /= 2; e++; }
    while (v < 0.5 && e > 0)  { v *= 2; e--; }
    int m = (int)(v * 16);
    if (m > 15) m = 15;
    return (s << 7) | (e << 4) | m;
}



bool CPU::execute(const Instruction &instruction, Memory &memory, InputOutput &io) {
    int op = hexToInt(instruction.getOpcode());
    int R  = hexToInt(instruction.getOperand1());
    int XY = hexToInt(instruction.getOperand2() + instruction.getOperand3());

switch (op) {
    case 1:
        registers[R].setValue(memory.read(XY));
        break;

    case 2:
        registers[R].setValue(intToHex(XY));
        break;

    case 3:
        if (XY == 0) io.printOutput(registers[R].getValue());
        else memory.write(XY, registers[R].getValue());
        break;

    case 4: {
        int src = hexToInt(instruction.getOperand2());
        int dst = hexToInt(instruction.getOperand3());
        registers[dst].setValue(registers[src].getValue());
        break;
    }
    case 5: {
        int S = hexToInt(instruction.getOperand2());
        int T = hexToInt(instruction.getOperand3());
        int a = hexToInt(registers[S].getValue());
        int b = hexToInt(registers[T].getValue());
        registers[R].setValue(intToHex(a + b));
        break;
    }
    case 6: {
        int S = hexToInt(instruction.getOperand2());
        int T = hexToInt(instruction.getOperand3());
        double a = byteToFloat(hexToInt(registers[S].getValue()));
        double b = byteToFloat(hexToInt(registers[T].getValue()));
        registers[R].setValue(intToHex(floatToByte(a + b)));
        break;
    }
    case 7: {
        int S = hexToInt(instruction.getOperand2());
        int T = hexToInt(instruction.getOperand3());
        registers[R].setValue(intToHex(hexToInt(registers[S].getValue()) | hexToInt(registers[T].getValue())));
        break;
    }
    case 8: {
        int S = hexToInt(instruction.getOperand2());
        int T = hexToInt(instruction.getOperand3());
        registers[R].setValue(intToHex(hexToInt(registers[S].getValue()) & hexToInt(registers[T].getValue())));
        break;
    }
    case 9: {
        int S = hexToInt(instruction.getOperand2());
        int T = hexToInt(instruction.getOperand3());
        registers[R].setValue(intToHex(hexToInt(registers[S].getValue()) ^ hexToInt(registers[T].getValue())));
        break;
    }
    case 10: {
        int x = hexToInt(instruction.getOperand3()) % 8;
        int v = hexToInt(registers[R].getValue());
        v = ((v >> x) | (v << (8 - x))) & 0xFF;
        registers[R].setValue(intToHex(v));
        break;

    }
    case 11: {
        if (registers[R].getValue() == registers[0].getValue()) pc = XY;
        break;
    }
    case 12:
        return false;

    default:
        break;
}

    return true;

}

