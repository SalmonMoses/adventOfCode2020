#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void taskOne() {
    ifstream input("input.txt");
    string curLine;
    vector<int> numbers;
    while(getline(input, curLine)) {
        int number = stoi(curLine);
        for (auto it = begin(numbers); it != end(numbers); ++it) {
            if ((number + *it) == 2020) {
                cout << number * (*it) << endl;
            }
        }
        numbers.push_back(number);
    }
}

void taskTwo() {
    ifstream input("input.txt");
    string curLine;
    vector<int> numbers;
    while(getline(input, curLine)) {
        int number = stoi(curLine);
        for (auto first = begin(numbers); first != end(numbers); ++first) {
            for (auto second = begin(numbers) + 1; second != end(numbers); ++second) {
                if ((number + *first + *second) == 2020) {
                    cout << number * (*first) * (*second) << endl;
                }
            }
        }
        numbers.push_back(number);
    }
}

int main() {
    taskTwo();
    return 0;
}
