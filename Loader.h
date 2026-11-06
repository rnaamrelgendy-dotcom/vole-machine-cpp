#pragma once
#include <string>
using namespace std;

class Memory;

class Loader {
private:
    string filename;
    int startAddress;
public:
    bool loadprogram(string filename , int startAddress, Memory& memory);
    bool validateAddress(int address);
    string sanitizeLine(string line);
};

