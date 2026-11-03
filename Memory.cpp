#include "Memory.h"

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