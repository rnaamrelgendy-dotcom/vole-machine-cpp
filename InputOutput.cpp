#include "InputOutput.h"
#include<iostream>
using namespace std;

string InputOutput::readInput(string prompt) {
    if (inputHandler) return inputHandler(prompt);
    cout<<prompt <<endl;
    string input;
    getline(cin,input);
    return input;
}

void InputOutput::printOutput(string text) {
    if (outputHandler) { outputHandler(text); return; }
    cout<<text<<endl;
}