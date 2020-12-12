#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

void taskOne() {
    std::ifstream input("data/input.txt");
    std::vector<uint32_t> jolts;
    std::string curLine;
    while (std::getline(input, curLine)) {
        jolts.push_back(std::stoul(curLine));
    }

    std::sort(jolts.begin(), jolts.end());

    uint32_t oneDiffJolts = 0;
    uint32_t threeDiffJolts = 0;
    if (jolts[0] == 1) {
        oneDiffJolts++;
    } else if (jolts[0] == 3) {
        threeDiffJolts++;
    }
    for (size_t i = 1; i < jolts.size(); ++i) {
        if (jolts[i] - jolts[i - 1] == 1) {
            oneDiffJolts++;
        } else if (jolts[i] - jolts[i - 1] == 3) {
            threeDiffJolts++;
        } else {
            std::cout << "Error! Difference is neither 1 nor 3!" << std::endl;
        }
    }
    threeDiffJolts++;

    std::cout << "1-difference jolts = " << oneDiffJolts << std::endl;
    std::cout << "3-difference jolts = " << threeDiffJolts << std::endl;
    std::cout << oneDiffJolts * threeDiffJolts << std::endl;
}

void taskTwo() {
    std::ifstream input("data/input.txt");
    std::vector<uint32_t> jolts{0};
    std::string curLine;
    while (std::getline(input, curLine)) {
        jolts.push_back(std::stoul(curLine));
    }

    std::sort(jolts.begin(), jolts.end());
    jolts.push_back(jolts.back() + 3);

    std::map<int32_t, uint64_t> joltArrangements;
    joltArrangements[jolts.size() - 1] = 1;
    for (int32_t i = jolts.size() - 2; i >= 0; --i) {
        joltArrangements[i] = 0;
        if (jolts.size() - i > 1 && jolts[i + 1] - jolts[i] <= 3) {
            joltArrangements[i] += joltArrangements[i + 1];
        }
        if (jolts.size() - i > 2 && jolts[i + 2] - jolts[i] <= 3) {
            joltArrangements[i] += joltArrangements[i + 2];
        }
        if (jolts.size() - i > 3 && jolts[i + 3] - jolts[i] <= 3) {
            joltArrangements[i] += joltArrangements[i + 3];
        }
    }

    std::cout << joltArrangements[0] << std::endl;
}

int main() {
    taskTwo();
    return 0;
}
