//
// Created by misha on 08.12.2020.
//

#ifndef DAY8_VM_H
#define DAY8_VM_H

#include <vector>

enum class CommandType {
    ACC,
    JMP,
    NOP
};

struct Command {
    CommandType cmdType;
    int arg;
    bool wasExecuted;
};

class VM {
private:
    unsigned int ip = 0;
    int acc = 0;
    std::vector<Command> originalProgram;
    std::vector<Command> program;
public:
    VM();
    void loadFromFile(const std::string &filePath);
    int execute();
    int repairMutationally();
    inline void resetState();
};


#endif //DAY8_VM_H
