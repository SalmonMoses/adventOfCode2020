#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

unsigned int calculateSeatNumber(std::string &seatDesc) {
    std::replace(seatDesc.begin(), seatDesc.begin() + 7, 'B', '1');
    std::replace(seatDesc.begin(), seatDesc.begin() + 7, 'F', '0');
    std::replace(seatDesc.begin() + 7, seatDesc.end(), 'R', '1');
    std::replace(seatDesc.begin() + 7, seatDesc.end(), 'L', '0');
    return std::stoi(seatDesc, nullptr, 2);
}

void taskOne() {
    std::ifstream input("input.txt");
    std::string currentSeatDesc;
    unsigned int maxSeatNumber = std::numeric_limits<unsigned int>::min();
    while (std::getline(input, currentSeatDesc)) {
        unsigned int seatNumber = calculateSeatNumber(currentSeatDesc);
        if (seatNumber > maxSeatNumber) {
            maxSeatNumber = seatNumber;
        }
    }
    std::cout << maxSeatNumber << std::endl;
}

void taskTwo() {
    std::ifstream input("input.txt");
    std::string currentSeatDesc;
    std::vector<unsigned int> seats;
    while (std::getline(input, currentSeatDesc)) {
        seats.push_back(calculateSeatNumber(currentSeatDesc));
    }
    for (unsigned int seat : seats) {
        if (std::find(seats.begin(), seats.end(), seat + 1) == seats.end()
            && std::find(seats.begin(), seats.end(), seat + 2) != seats.end()) {
            std::cout << seat + 1 << std::endl;
        }
    }
}

int main() {
    taskTwo();
    return 0;
}
