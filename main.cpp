#include <iostream>
#include "Machine.h"
using namespace std;

int main() {
    Machine machine;
    string filename;
    cout << "Enter program filename: ";
    cin >> filename;
    if (!machine.loadProgram(filename)) {
        cout << "Failed to load program!\n";
        return 1;
    }
    machine.run();
    machine.displayStats();
    machine.displayRegisters();
    machine.displayMemory();

    return 0;
}