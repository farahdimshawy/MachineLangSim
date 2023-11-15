//
// Created by Admin on 11/13/2023.
//

#ifndef MACHINESIMULATOR_MACHINE_H
#define MACHINESIMULATOR_MACHINE_H
#include "memory.h"

class Machine;
class InstructionRegister{
public:
    string input;
    Instruction i;
    Register r;
    InstructionRegister();
    friend class Machine;
};
class Machine {
private:
    [[nodiscard]] static int hexCharToDecimal(char hexChar) {
        if (hexChar >= '0' && hexChar <= '9') {
            return hexChar - '0';
        } else if (hexChar >= 'A' && hexChar <= 'F') {
            return hexChar - 'A' + 10;
        } else if (hexChar >= 'a' && hexChar <= 'f') {
            return hexChar - 'a' + 10;
        } else {
            return 0; // Invalid character, default to 0
        }
    }
    [[nodiscard]] static string toHexString(int value) {
        ostringstream oss;
        oss << uppercase << hex << setw(2) << setfill('0') << to_string(value);
        return oss.str();
    }
    bool halt;
public:
    InstructionRegister IR;
    string screen;
    int programcounter{}; //contains address of next instruction and increments by 2
    vector<Register> RegisterArray; //contains all 16 registers and their content
    vector<memory> MemoryArray; //contains all 256 memory addresses and their content

    Machine();
    ~Machine();

    bool valid_value(string ins);
    bool halted();
    void initializeMemory();//initializes memory addresses to contain zeroes
    void displayMemory() const;//displays the memory
    void initializeRegister();//initializes all registers to contain zeroes
    void displayRegister() const;//displays the registers
    void read(const string& filename);//reads machine language code file and stores it in memory
    string extractString(int StartAddress);
    void execute();
    void reset();
    string screen_content();

    friend class InstructionRegister;
};
#endif //MACHINESIMULATOR_MACHINE_H
