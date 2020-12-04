#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>

const size_t MAP_WIDTH = 31;

using Map = std::vector<std::vector<bool>>;

Map initMap(const std::string& fileName) {
    Map result;
    std::ifstream input(fileName);
    std::string curString;
    while(std::getline(input, curString)) {
        std::vector<bool> line{};
        for(auto it = std::cbegin(curString); it != std::cend(curString); ++it) {
            line.push_back(*it == '#');
        }
        result.push_back(line);
    }
    return result;
}

unsigned int traverseMap(Map map, size_t dx, size_t dy) {
    unsigned int treesEncountered = 0;
    size_t mapHeight = map.size();
    size_t mapWidth = map[0].size();
    size_t x = 0;
    for(size_t y = 0; y < mapHeight; y += dy) {
        auto line = map[y];
        if(line[x]) {
            treesEncountered++;
        }
        x = (x + dx) % mapWidth;
    }
    return treesEncountered;
}

void taskOne() {
    auto map = initMap("input.txt");
    unsigned int treesEncountered = traverseMap(map, 3, 1);
    std::cout << treesEncountered << std::endl;
}

void taskTwo() {
    auto map = initMap("input.txt");
    unsigned int treesEncountered = traverseMap(map, 1, 1);
    treesEncountered *= traverseMap(map, 3, 1);
    treesEncountered *= traverseMap(map, 5, 1);
    treesEncountered *= traverseMap(map, 7, 1);
    treesEncountered *= traverseMap(map, 1, 2);
    std::cout << treesEncountered << std::endl;
}

int main() {
    taskTwo();
    return 0;
}
