#include <string>
using namespace std;
#pragma once

class Register {
private:
    string value;
public:
    Register();
    string getValue();
    void setValue(string newVal);
    void clear();
};













