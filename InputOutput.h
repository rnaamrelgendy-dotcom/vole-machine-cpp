#ifndef VOLEMACHINE_INPUTOUTPUT_H
#define VOLEMACHINE_INPUTOUTPUT_H
#include <string>
using namespace std;

class InputOutput {
public:
    string readInput(string prompt);
    void printOutput(string text);
};

#endif