//
// Created by Admin on 11/13/2023.
//

#include "memory.h"

// Function to calculate the two's complement of a binary number
std::bitset<32> twosComplement(const std::bitset<32>& binary) {
    return std::bitset<32>(-binary.to_ulong());
}


// Function to convert hexadecimal to binary
bitset<32> hexToBinary(const std::string& hexString) {
    std::istringstream iss(hexString);
    unsigned int hexValue;
    iss >> std::hex >> hexValue;
    return std::bitset<32>(hexValue);
}
Register Register:: operator+(Register s){
    bitset<32> newval = twosComplement(hexToBinary(to_string(s.value)));
    bitset<32> val = twosComplement(hexToBinary(to_string(this->value)));
    //incomplete
}
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