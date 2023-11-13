//
// Created by Admin on 11/13/2023.
//

#include "Machine.h"
#include<iomanip>
void Machine::initializeMemory() {
    for (int i = 0; i <= 0xFF; ++i) {
        MemoryArray.push_back(memory(i));
    }
}
void Machine::displayMemory() const{
    for (const memory& mem : MemoryArray) {
        std::cout << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << mem.address << " "
                  << std::setw(2) << std::setfill('0') << mem.value << std::dec << std::endl;
    }
}
Machine:: Machine(){
    initializeMemory();
    initializeRegister();
}
void Machine::initializeRegister() {
    for(int i = 0; i <= 16; i++){
        RegisterArray.push_back(Register(i));
    }
}
void Machine::displayRegister() const {
    for(const Register& r: RegisterArray){
        cout << uppercase << hex << setw(2) << setfill('0') << r.name << " " << setw(2) << setfill('0') << r.value<< dec << '\n';
    }
}
void Machine::read(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "error opening file\n";
        return;
    }
    char hex1, hex2; //read two characters at a time
    int address = 0; //start from address 0
    while (file >> setw(1) >> hex1 >> setw(1) >> hex2) {
        int value = hexCharToDecimal(hex1) << 4 | hexCharToDecimal(hex2);
        //shift hex1 to the left by 4 positions and combine it (using OR) with hex2 decimal value in an integer
        // Store the value in memory
        if (address < static_cast<int>(MemoryArray.size())) {
            MemoryArray[address].value = value;
        }
        ++address;
    }
    file.close();

}


