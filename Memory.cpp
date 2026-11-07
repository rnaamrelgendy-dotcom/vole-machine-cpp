#include "Memory.h"
#include <sstream>
#include <iomanip>
#include"InputOutput.h"

Memory::Memory(){
    for(string &c: cell){
        c="00";
    }
}

bool Memory::isValidAddress(int i){
    if (i >=0 && i<= 255){
        return true;
    }
    else{
        return false;
    }
}
string Memory::read(int i){
    if(isValidAddress(i)){
        return cell[i];
    }
    else{
        return "fail";
    }
}
bool Memory::write(int i, string val){
    if(isValidAddress(i)){
        cell[i]= val;
        return true;
    }
    else{
        return false;
    }
}


void Memory::clear(){
    for(string &c: cell){
        c="00";
    }
}

void Memory::displayMemory(InputOutput& io) const {
    io.printOutput("_________ MEMORY _________");

    for (int i = 0; i < 256; i++) {
        stringstream ss;
        ss << hex << uppercase << setw(2) << setfill('0') << i;

        io.printOutput(ss.str() + ": " + cell[i]);
    }
}