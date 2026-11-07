#include <string>
#pragma once
#include"InputOutput.h"
using namespace std;

class Memory {
private:
    string cell[256];

public:
    Memory();

    bool isValidAddress(int i);
    string read(int i);
    bool write(int i, string val);
    void clear();
    void displayMemory(InputOutput& io) const;


};