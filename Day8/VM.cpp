//
// Created by misha on 08.12.2020.
//

#include <fstream>
#include <string>
#include <iostream>
#include <set>
#include "VM.h"

VM::VM() {}

void VM::loadFromFile(const std::string &filePath) {
    std::ifstream input("input.txt");
    std::string cmd;
    while (std::getline(input, cmd)) {
        auto separatorPos = cmd.find(' ');
        std::string command = cmd.substr(0, separatorPos);
        std::string argument = cmd.substr(separatorPos);
        int arg = std::stoi(argument);
        std::cout << command << ' ' << arg << std::endl;
        CommandType type;
        if (command == "acc") {
            type = CommandType::ACC;
        } else if (command == "jmp") {
            type = CommandType::JMP;
        } else if (command == "nop") {
            type = CommandType::NOP;
        }
        this->originalProgram.push_back(Command{type, arg});
    }
    program = this->originalProgram;
}

int VM::execute() {
    std::set<unsigned int> executedCommands;
    while (ip < program.size()) {
        if (executedCommands.find(ip) != executedCommands.end()) {
            throw std::string("On entering infinite loop accumulator was " + acc);
        }
        Command curCommand = program[ip];
        executedCommands.insert(ip);
        switch (curCommand.cmdType) {
            case CommandType::ACC: this->acc += curCommand.arg;
                ip++;
                break;
            case CommandType::JMP: this->ip += curCommand.arg;
                break;
            case CommandType::NOP: ip++;
        }
    }
    return acc;
}

int VM::repairMutationally() {
    for(int i = 0; i < originalProgram.size(); ++i) {
        Command cmdToMutate = originalProgram[i];
        if(cmdToMutate.cmdType == CommandType::JMP) {
            cmdToMutate.cmdType = CommandType::NOP;
            program[i] = cmdToMutate;
        } else if(cmdToMutate.cmdType == CommandType::NOP) {
            cmdToMutate.cmdType = CommandType::JMP;
            program[i] = cmdToMutate;
        }
        try {
            return this->execute();
        } catch (int e) {
            this->resetState();
            continue;
        }
    }
}

inline void VM::resetState() {
    program = originalProgram;
    ip = 0;
    acc = 0;
}
