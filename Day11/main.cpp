#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <algorithm>

const uint32_t MAP_WIDTH = 92;
const uint32_t MAP_HEIGHT = 90;

enum class CellState {
    FLOOR,
    EMPTY,
    OCCUPIED
};

using CellMap = std::array<std::array<CellState, MAP_WIDTH>, MAP_HEIGHT>;

bool rayTraceOccupiedSeat(CellMap &map, uint32_t x, uint32_t y, int32_t dx, int32_t dy) {
    x += dx;
    y += dy;
    while (x < MAP_WIDTH && y < MAP_HEIGHT) {
//        if (map[y][x] == CellState::EMPTY) { return false; }
        if (map[y][x] == CellState::OCCUPIED) { return true; }
        x += dx;
        y += dy;
    }
    return false;
}

void taskOne() {
    std::ifstream input("input.txt");
    CellMap cells{};
    uint32_t curX = 0;
    uint32_t curY = 0;
    std::string curLine;
    while (std::getline(input, curLine)) {
        for (const char &c : curLine) {
            switch (c) {
                case '.': cells[curY][curX++] = CellState::FLOOR;
                    break;
                case 'L': cells[curY][curX++] = CellState::EMPTY;
                    break;
                case '#': cells[curY][curX++] = CellState::OCCUPIED;
                    break;
                default: continue;
            }
        }
        curY++;
        curX = 0;
    }

    CellMap transientState = cells;
    uint32_t changes;
    do {
        changes = 0;
        for (size_t y = 0; y < MAP_HEIGHT; ++y) {
            for (size_t x = 0; x < MAP_WIDTH; ++x) {
                uint32_t adjacentOccupied = 0;
                if (cells[y][x] == CellState::FLOOR) {
                    transientState[y][x] = CellState::FLOOR;
                    continue;
                }

                try {
                    if (cells.at(y - 1).at(x - 1) == CellState::OCCUPIED) {
                        adjacentOccupied++;
                    }
                } catch (const std::out_of_range &) {}
                try {
                    if (cells.at(y - 1).at(x) == CellState::OCCUPIED) {
                        adjacentOccupied++;
                    }
                } catch (const std::out_of_range &) {}
                try {
                    if (cells.at(y - 1).at(x + 1) == CellState::OCCUPIED) {
                        adjacentOccupied++;
                    }
                } catch (const std::out_of_range &) {}
                try {
                    if (cells.at(y).at(x - 1) == CellState::OCCUPIED) {
                        adjacentOccupied++;
                    }
                } catch (const std::out_of_range &) {}
                try {
                    if (cells.at(y).at(x + 1) == CellState::OCCUPIED) {
                        adjacentOccupied++;
                    }
                } catch (const std::out_of_range &) {}
                try {
                    if (cells.at(y + 1).at(x - 1) == CellState::OCCUPIED) {
                        adjacentOccupied++;
                    }
                } catch (const std::out_of_range &) {}
                try {
                    if (cells.at(y + 1).at(x) == CellState::OCCUPIED) {
                        adjacentOccupied++;
                    }
                } catch (const std::out_of_range &) {}
                try {
                    if (cells.at(y + 1).at(x + 1) == CellState::OCCUPIED) {
                        adjacentOccupied++;
                    }
                } catch (const std::out_of_range &) {}

                if (cells[y][x] == CellState::EMPTY && adjacentOccupied == 0) {
                    transientState[y][x] = CellState::OCCUPIED;
                    changes++;
                } else if (cells[y][x] == CellState::OCCUPIED && adjacentOccupied >= 4) {
                    transientState[y][x] = CellState::EMPTY;
                    changes++;
                }
            }
        }
        cells = transientState;
    } while (changes > 0);

    uint32_t occupiedSeats = 0;
    for (size_t y = 0; y < MAP_HEIGHT; ++y) {
        for (size_t x = 0; x < MAP_WIDTH; ++x) {
            if (cells.at(y).at(x) == CellState::OCCUPIED) { occupiedSeats++; }
        }
    }
    std::cout << occupiedSeats << std::endl;
}

void taskTwo() {
    std::ifstream input("input.txt");
    CellMap cells{};
    uint32_t curX = 0;
    uint32_t curY = 0;
    std::string curLine;
    while (std::getline(input, curLine)) {
        for (const char &c : curLine) {
            switch (c) {
                case '.': cells[curY][curX++] = CellState::FLOOR;
                    break;
                case 'L': cells[curY][curX++] = CellState::EMPTY;
                    break;
                default: continue;
            }
        }
        curY++;
        curX = 0;
    }

    CellMap transientState = cells;
    uint32_t changes;
    do {
        changes = 0;
        for (size_t y = 0; y < MAP_HEIGHT; ++y) {
            for (size_t x = 0; x < MAP_WIDTH; ++x) {
                uint32_t adjacentOccupied = 0;
                if (cells[y][x] == CellState::FLOOR) {
                    transientState[y][x] = CellState::FLOOR;
                    continue;
                }

                if (rayTraceOccupiedSeat(cells, x, y, -1, -1)) { adjacentOccupied++; }
                if (rayTraceOccupiedSeat(cells, x, y, 0, -1)) { adjacentOccupied++; }
                if (rayTraceOccupiedSeat(cells, x, y, 1, -1)) { adjacentOccupied++; }
                if (rayTraceOccupiedSeat(cells, x, y, -1, 0)) { adjacentOccupied++; }
                if (rayTraceOccupiedSeat(cells, x, y, 1, 0)) { adjacentOccupied++; }
                if (rayTraceOccupiedSeat(cells, x, y, -1, 1)) { adjacentOccupied++; }
                if (rayTraceOccupiedSeat(cells, x, y, 0, 1)) { adjacentOccupied++; }
                if (rayTraceOccupiedSeat(cells, x, y, 1, 1)) { adjacentOccupied++; }


                if (cells[y][x] == CellState::EMPTY && adjacentOccupied == 0) {
                    transientState[y][x] = CellState::OCCUPIED;
                    changes++;
                } else if (cells[y][x] == CellState::OCCUPIED && adjacentOccupied >= 5) {
                    transientState[y][x] = CellState::EMPTY;
                    changes++;
                }
            }
        }
        cells = transientState;
    } while (changes > 0);

    uint32_t occupiedSeats = 0;
    for (size_t y = 0; y < MAP_HEIGHT; ++y) {
        for (size_t x = 0; x < MAP_WIDTH; ++x) {
            if (cells[y][x] == CellState::OCCUPIED) { occupiedSeats++; }
        }
    }
    std::cout << occupiedSeats << std::endl;
}

int main() {
    taskTwo();
    return 0;
}
