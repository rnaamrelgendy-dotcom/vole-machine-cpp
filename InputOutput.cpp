#include "InputOutput.h"
#include<iostream>
using namespace std;

string InputOutput::readInput(string prompt) {
    cout<<prompt <<endl;
    string input;
    getline(cin,input);
    return input;
}

void InputOutput::printOutput(string text) {
    cout<<text<<endl;
}
