//
// Created by Admin on 11/13/2023.
//

#include "memory.h"

Register Register:: operator=(Register s){
    value=s.value;
    return *this;
}
Register Register:: operator=(memory m){
    value=m.value;
    return *this;
}
Register Register:: operator=(int x){
    value=x;
    return *this;
}

Register::Register() {};

memory::memory() {};