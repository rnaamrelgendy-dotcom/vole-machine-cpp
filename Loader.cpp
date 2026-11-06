#include "Loader.h"
#include <iostream>
#include <string>
#include<fstream>
#include "Memory.h"
using namespace std;

bool Loader::validateAddress(int address) {
    if (address >= 0 && address < 256) return true;
    else return false;
}

string Loader::sanitizeLine(string line) {
    while (!line.empty() && line[0] == ' ') {
        line = line.erase(0,1);
    }
    while (!line.empty() && line.back() == ' ') {
        line.pop_back();
    }
    return line;
}

bool Loader::loadprogram(string filename, int startAddress, Memory& memory) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error: Cannot open file!" << endl;
        return false;
    }
    string line;
    int address = startAddress;
    while (getline(file,line)) {
        line = sanitizeLine(line);
        if (line.empty()) continue;
        if (!validateAddress(address)) {
            cout << "Invalid address" << endl;
            file.close();
            return false;
        }
        if (!validateAddress(address + 1)) {
            cout << "Invalid address" << endl;
            file.close();
            return false;
        }

        memory.write(address, line.substr(0, 2));
        memory.write(address + 1, line.substr(2, 2));

        address += 2;
    }
    file.close();
    return true;
}



