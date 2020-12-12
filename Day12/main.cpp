#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Vector2i {
    int64_t x;
    int64_t y;

    Vector2i(int64_t x, int64_t y) : x(x), y(y) {}

    int64_t manhattanDistance() const {
        return std::abs(this->x) + std::abs(this->y);
    }

    int64_t manhattanDistance(Vector2i &rhs) const {
        return std::abs(this->x - rhs.x) + std::abs(this->y - rhs.y);
    }

    Vector2i rotateClockwise(int64_t degrees) {
        Vector2i result = *this;
        for (int i = 0; i < degrees / 90; ++i) {
            int64_t newY = -result.x;
            result.x = result.y;
            result.y = newY;
        }
        return result;
    }

    Vector2i operator+(Vector2i rhs) {
        return {this->x + rhs.x, this->y + rhs.y};
    }

    Vector2i operator*(int64_t k) {
        return {this->x * k, this->y * k};
    }
};

void taskOne() {
    std::ifstream input("input.txt");
    std::string curLine;
    Vector2i location = {0, 0};
    Vector2i direction = {1, 0};
    while (std::getline(input, curLine)) {
        char movementDirection = curLine[0];
        int64_t movementAmount = std::stoi(curLine.substr(1));
        std::cout << movementDirection << " " << movementAmount << std::endl;

        switch(movementDirection) {
            case 'N': location = location + Vector2i(0, 1) * movementAmount; break;
            case 'S': location = location + Vector2i(0, -1) * movementAmount; break;
            case 'E': location = location + Vector2i(1, 0) * movementAmount; break;
            case 'W': location = location + Vector2i(-1, 0) * movementAmount; break;
            case 'R': direction = direction.rotateClockwise(movementAmount); break;
            case 'L': direction = direction.rotateClockwise(movementAmount * 3); break;
            case 'F': location = location + direction * movementAmount; break;
        }
    }
    std::cout << std::endl << "Result = " << location.manhattanDistance() << std::endl;
}

void taskTwo() {
    std::ifstream input("input.txt");
    std::string curLine;
    Vector2i ship = {0, 0};
    Vector2i waypoint = {10, 1};
    while (std::getline(input, curLine)) {
        char movementDirection = curLine[0];
        int64_t movementAmount = std::stoi(curLine.substr(1));
        std::cout << movementDirection << " " << movementAmount << std::endl;

        switch(movementDirection) {
            case 'N': waypoint = waypoint + Vector2i(0, 1) * movementAmount; break;
            case 'S': waypoint = waypoint + Vector2i(0, -1) * movementAmount; break;
            case 'E': waypoint = waypoint + Vector2i(1, 0) * movementAmount; break;
            case 'W': waypoint = waypoint + Vector2i(-1, 0) * movementAmount; break;
            case 'R': waypoint = waypoint.rotateClockwise(movementAmount); break;
            case 'L': waypoint = waypoint.rotateClockwise(movementAmount * 3); break;
            case 'F': ship = ship + waypoint * movementAmount; break;
        }
    }
    std::cout << std::endl << "Result = " << ship.manhattanDistance() << std::endl;
}

int main() {
    taskTwo();
    return 0;
}
