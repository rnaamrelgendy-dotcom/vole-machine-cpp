#include <Register.h>

Register::Register(){
    value = "00";
}

string Register::getValue(){
    return value;
}

void Register::setValue(string newVal){
    value = newVal;
}

void Register::clear(){
    value = "00";
}
