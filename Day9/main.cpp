#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <vector>
#include <numeric>

const size_t BUFFER_SIZE = 25;
const uint64_t INVALID_NUMBER = 1721308972;

bool checkSum(std::array<uint64_t, BUFFER_SIZE> buffer, uint64_t check) {
    for (int i = 0; i < buffer.size(); ++i) {
        for (int j = i + 1; j < buffer.size(); ++j) {
            if (buffer[i] + buffer[j] == check) {
                return true;
            }
        }
    }
    return false;
}

uint64_t taskOne() {
    std::ifstream input("input.txt");
    std::string curLine;
    std::array<uint64_t, BUFFER_SIZE> buffer{};
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        std::getline(input, curLine);
        buffer[i] = std::stoul(curLine);
    }
    size_t currentPositionInFile = 25;
    while (std::getline(input, curLine)) {
        uint64_t curNumber = std::stoul(curLine);
        if (!checkSum(buffer, curNumber)) {
            return curNumber;
        } else {
            buffer[currentPositionInFile % BUFFER_SIZE] = curNumber;
            ++currentPositionInFile;
        }
    }
}

void taskTwo() {
    std::ifstream input("input.txt");
    std::string curLine;
    std::vector<uint64_t> numbers;
    size_t begin = 0;
    size_t end = 0;
    uint64_t curNumber;
    do {
        if (std::getline(input, curLine)) {
            curNumber = std::stoull(curLine);
            numbers.push_back(curNumber);
//            end++;
        }
        uint64_t sum = std::accumulate(numbers.begin() + begin, numbers.begin() + end, curNumber);
        if (sum < INVALID_NUMBER) {
            end++;
        } else if (sum > INVALID_NUMBER) {
            begin++;
        } else {
            std::cout << numbers.front() + numbers.back() << std::endl;
            return;
        }
    } while (begin != end);
}

int main() {
//    std::cout << taskOne() << std::endl;
    taskTwo();
    return 0;
}
