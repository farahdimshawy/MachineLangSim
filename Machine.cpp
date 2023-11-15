//
// Created by Admin on 11/13/2023.
//

#include "Machine.h"


bitset<16> Sum(const std::bitset<16>& num1, const std::bitset<16>& num2);
InstructionRegister::InstructionRegister(){};
Machine:: Machine(): programcounter(0), IR(), screen(""){
    initializeMemory();
    initializeRegister();

}
Machine::~Machine()
{
}

void Machine::initializeMemory() {
    for (int i = 0; i <= 0xFF; ++i) {
        MemoryArray.emplace_back(i);
    }
}
void Machine::displayMemory() const{
    for (const memory& mem : MemoryArray) {
        std::cout << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << mem.address << " "
                  << std::setw(2) << std::setfill('0') << mem.value << std::dec << std::endl;
    }
}
void Machine::initializeRegister() {
    for(int i = 0; i <= 16; i++){
        RegisterArray.emplace_back(i);
    }
}
void Machine::displayRegister() const {
    for(const Register& r: RegisterArray){
        cout << uppercase << hex << setw(2) << setfill('0') << r.name << " " << setw(2) << setfill('0') << r.value << '\n';
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
void Machine::execute(){
    while(programcounter<=256) {
        this->IR.input = extractString(programcounter);
        //extract the instruction register from memory
        bool val= valid_value(this->IR.input); //check if the instruction is valid
        if(val) {
            this->IR.i.name = this->IR.input[0];    //extract type of instruction
            this->IR.r.name = this->IR.input[1] - '0'; //extract register name/ register array index
            //load from memory into register
            if (this->IR.i.name == '1') {
                int address = stoi(this->IR.input.substr(this->IR.input.length() - 2, 2), nullptr, 16);
                RegisterArray[this->IR.r.name].value = MemoryArray[address].value;
            }
                //load bit pattern into register
            else if (this->IR.i.name == '2') {
                string s = this->IR.input.substr(this->IR.input.length() - 2, 2);
                RegisterArray[this->IR.r.name].value = stoi(s, nullptr,16);
                //16 ensures the conversion from hexa to decimal
            }
                //store from register into memory
            else if (this->IR.i.name == '3') {
                int address = stoi(this->IR.input.substr(this->IR.input.length() - 2, 2), nullptr, 16);
                if (address == 00) {
                    stringstream ss;
                    ss << uppercase << hex << setw(2) << setfill('0') << RegisterArray[this->IR.r.name].value;
                    screen+=(ss.str());
                } else {
                    MemoryArray[address].value = RegisterArray[this->IR.r.name].value;
                }
            }
                //move from register s to register t
            else if (this->IR.i.name == '4') {
                int s = this->IR.input[2] - '0'; //converting register number from string to register array index
                int t = this->IR.input[3] - '0';
                RegisterArray[t].value = RegisterArray[s].value;
            }
                //add two numbers in 2's complement form
            else if (this->IR.i.name == '5') {
                int s = RegisterArray[this->IR.input[2] -
                                      '0'].value; //converting register number from string to register array index
                int t = RegisterArray[this->IR.input[3] - '0'].value;
                std::bitset<16> binaryNum1(s);
                std::bitset<16> binaryNum2(t);
                // Calculate the sum (considering two's complement)
                std::bitset<16> sumBinary = Sum(binaryNum1, binaryNum2);
                int sum = static_cast<int>(sumBinary.to_ulong());
                RegisterArray[this->IR.r.name].value = sum;
            }
                //jump if content of r is equal to content of register zero
            else if (this->IR.i.name == 'b') {
                int address = stoi(this->IR.input.substr(this->IR.input.length() - 2, 2), nullptr, 16);
                if (RegisterArray[this->IR.r.name].value == RegisterArray[0].value)
                    programcounter = address;
            }
                //halt program
            else if (this->IR.i.name == 'c') {
                exit(0);
            }
            programcounter += 2;
        }
        else {
            cout << "invalid instruction\n";
            break;
        }
    }
}
void Machine::reset()
{
    for (int i{}; i < 16; i++)
    {
        RegisterArray[i].value = 0;
    }
    for (int i{}; i < 256; i++)
    {
        MemoryArray[i].value = 0;
    }
    programcounter = 0;
    halt = false;

}

bool Machine::valid_value(string ins)
{
    for (char c: ins)
    {
        if (c < '0' || c > '16')
        {
            return false;
        }
    }
    return true;
}
bool Machine::halted()
{
    return halt;
}

string Machine::screen_content(){
    return screen;
}
string Machine::extractString(int StartAddress) {
    string s;
    std::stringstream s1;
    s1 << setw(2) << setfill('0') << std::hex << MemoryArray[StartAddress].value;  // Convert decimal to hexadecimal
    std::stringstream s2;
    s2 << setw(2)<< setfill('0') <<std::hex << MemoryArray[StartAddress+1].value;  // Convert decimal to hexadecimal
    s = s1.str() + s2.str();
    return s;
}


bitset<16> BinaryAddition(const std::bitset<16>& a, const std::bitset<16>& b) {
    std::bitset<16> result;
    bool carry = false;

    for (int i = 0; i < 16; ++i) {
        bool bitA = a[i];
        bool bitB = b[i];

        // XOR for sum
        result[i] = bitA ^ bitB ^ carry;

        // Carry generation for the next iteration
        carry = (bitA & bitB) | ((bitA ^ bitB) & carry);
    }

    return result;
}
bitset<16> addTwoNumbers16Bits(const std::bitset<16>& num1, const std::bitset<16>& num2) {
    // Sum the binary numbers and mask to 16 bits
    std::bitset<16> sumBinary = BinaryAddition(num1, num2);

    // Check for overflow (if the most significant bit is different from the carry)
    bool overflow = (num1[15] == num2[15]) && (sumBinary[15] != num1[15]);

    // If overflow, set all bits to the most significant bit to represent the overflow value
    if (overflow) {
        sumBinary.set();
    }

    return sumBinary;
}
// Function to add two 16-bit numbers in two's complement and return the result in only two bytes
bitset<16> Sum(const std::bitset<16>& num1, const std::bitset<16>& num2) {
    // Sum the binary numbers
    std::bitset<16> sumBinary = addTwoNumbers16Bits(num1, num2);
    // Mask to 16 bits (to ensure it's only two bytes)
    return sumBinary;
}

