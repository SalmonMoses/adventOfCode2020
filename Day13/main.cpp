#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <ranges>

using namespace std;

vector<string> split(const string &str, const string &delim) {
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do {
        pos = str.find(delim, prev);
        if (pos == string::npos) { pos = str.length(); }
        string token = str.substr(prev, pos - prev);
        if (!token.empty()) { tokens.push_back(token); }
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}

void taskOne() {
    ifstream input("input.txt");
    uint32_t earliestTimestampToArrive;
    uint32_t earliestId = 0;
    uint32_t waitingAmount = numeric_limits<uint32_t>::max();
    input >> earliestTimestampToArrive;
    cout << earliestTimestampToArrive << endl;
    string busesLine;
    getline(input, busesLine);
    getline(input, busesLine);
    for (const string &bus : split(busesLine, ",")) {
        if (bus == "x") { continue; }
        uint32_t busId = stoi(bus);
        uint32_t busEta = busId - earliestTimestampToArrive % busId;
        if (busEta < waitingAmount) {
            waitingAmount = busEta;
            earliestId = busId;
        }
    }
    cout << earliestId * waitingAmount << endl;
}

void taskTwo() {
    ifstream input("input.txt");
    string curLine;
    string busesLine;
    getline(input, busesLine);
    getline(input, busesLine);
    vector<string> busIdsStrings = split(busesLine, ",");
    map<int32_t, int32_t> buses{};
    for (int i = 0; i < busIdsStrings.size(); ++i) {
        if(busIdsStrings[i] == "x") continue;
        auto busId = stoi(busIdsStrings[i]);
        buses[busId] = i;
    }
    for (auto &[busId, offset] : buses) {
        cout << "Bus ID: " << busId << " T+" << offset << endl;
    }
}

int main() {
    taskOne();
    cout << endl;
    taskTwo();
    return 0;
}
