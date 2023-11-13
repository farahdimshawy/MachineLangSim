#include <iostream>
#include <iomanip>
#include "Machine.h"
int main() {
    Machine myMachine;

    myMachine.read("test.txt");
    myMachine.displayMemory();
    return 0;

}
