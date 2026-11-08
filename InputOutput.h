#pragma once
#include <string>
#include <functional>
using namespace std;

class InputOutput {
public:
    function<void(const string&)> outputHandler;
    function<string(const string&)> inputHandler;
    string readInput(string prompt);
    void printOutput(string text);
};