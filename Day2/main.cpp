#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool boolXor(bool a, bool b) {
    return !a != !b;
}

struct Entry {
    Entry(unsigned int min, unsigned int max, char letter, const string &password) : min(min), max(max), letter(letter),
                                                                                     password(password) {}

    friend ostream &operator<<(ostream &os, const Entry &entry) {
        os << "min: " << entry.min << " max: " << entry.max << " letter: " << entry.letter << " password: "
           << entry.password;
        return os;
    }

    unsigned int min;
    unsigned int max;
    char letter;
    string password;

    bool checkCount() {
        unsigned int letterAppeared = 0;
        for (char c : this->password) {
            if (c == this->letter) { letterAppeared++; }
        }
        return (letterAppeared <= this->max) && (letterAppeared >= this->min);
    }

    bool checkPositions() {
        return boolXor(password[min - 1] == letter, password[max - 1] == letter);
    }
};

Entry parseEntry(string &input) {
    auto minNumEnd = input.find('-');
    auto minString = input.substr(0, minNumEnd);
    auto maxNumStart = minNumEnd + 1;
    auto maxNumEnd = input.find(' ');
    auto maxString = input.substr(maxNumStart, maxNumEnd);
    auto min = stoi(minString);
    auto max = stoi(maxString);
    auto letterEnd = input.find(':');
    auto letter = input.substr(maxNumEnd + 1, letterEnd)[0];
    auto password = input.substr(letterEnd + 2, input.length());
    return Entry(min, max, letter, password);
}

void taskOne() {
    ifstream passwords("input.txt");
    string curLine;
    unsigned int correctPasswords = 0;
    while (getline(passwords, curLine)) {
        Entry entry = parseEntry(curLine);
        cout << entry << endl;
        if(entry.checkCount()) {
            correctPasswords++;
        }
    }
    cout << correctPasswords << endl;
}

void taskTwo() {
    ifstream passwords("input.txt");
    string curLine;
    unsigned int correctPasswords = 0;
    while (getline(passwords, curLine)) {
        Entry entry = parseEntry(curLine);
        cout << entry << endl;
        if(entry.checkPositions()) {
            correctPasswords++;
        }
    }
    cout << correctPasswords << endl;
}

int main() {
    taskTwo();

    return 0;
}
