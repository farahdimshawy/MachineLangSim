//
// Created by Admin on 11/13/2023.
//

#ifndef MACHINESIMULATOR_MEMORY_H
#define MACHINESIMULATOR_MEMORY_H
#include <iostream>
#include <bitset>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class memory {
protected:
    int value{0};
    int address;
    //both values are in hexadecimal
public:
    memory();
    explicit memory(int add): value(0), address(add){}
    friend class Machine;
    friend class InstructionRegister;
    friend class Register;
};
class Register{
protected:
    int value;
    int name;
    //also hexadecimal
public:
    Register();
    explicit Register(int n): value(0), name(n){}
    Register operator+(Register s); //add register values
    Register operator=(memory m); //store memory value to register value
    Register operator=(int x);//store bit pattern in register
    Register operator=(Register r);//store two register values in another register (for sum)
    friend class Instruction;
    friend class Machine;
    friend class InstructionRegister;
};
class Instruction{
protected:
    int value{0};
    char name;
public:
    friend class InstructionRegister;
    friend class Machine;
};

#endif //MACHINESIMULATOR_MEMORY_H
