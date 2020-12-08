#include <iostream>
#include <fstream>
#include <string>
#include "VM.h"

void taskOne() {
    VM vm;
    vm.loadFromFile("input.txt");
    try {
        std::cout << vm.execute() << std::endl;
    } catch (std::string &acc) {
        std::cout << acc << std::endl;
    }
}

void taskTwo() {
    VM vm;
    vm.loadFromFile("input.txt");
    std::cout << vm.repairMutationally() << std::endl;
}

int main() {
    taskTwo();
    return 0;
}
