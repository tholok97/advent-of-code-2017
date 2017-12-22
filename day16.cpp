#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>

// abcdef 3
// x
//   x
void spin(std::vector<char>& programs, int length) {

    // WIP
        std::rotate(programs.begin(), programs.begin() + length, programs.end());
}

void exchange(std::vector<char>& programs, int pos1, int pos2) {

}

void partner(std::vector<char>& programs, char c1, char c2) {

}

std::vector<char> dance(std::string danceFile) {

    // init programs as vector of chars from 'a' to 'p'
    std::vector<char> programs;
    for (char c = 'a'; c <= 'e'; c++)
        programs.push_back(c);

    std::ifstream ifs(danceFile);

    char move;
    char dummyChar;
    while (ifs >> move) {
        switch(move) {
        case 's': 
            int length;
            ifs >> length >> dummyChar;
            spin(programs, length);
            break;
        case 'x': 
            int pos1, pos2;
            ifs >> pos1 >> dummyChar >> pos2 >> dummyChar;
            exchange(programs, pos1, pos2);
            break;
        case 'p': 
            char c1, c2;
            ifs >> c1 >> dummyChar >> c2 >> dummyChar;
            partner(programs, c1, c2);
            break;
        default: 
            std::cout << "ERROR! We don't know the move: " << move << std::endl;
        }
    }


    return programs;
}

void print(std::vector<char> d) {
    for (char c : d)
        std::cout << c;
    std::cout << std::endl;
}

int main() {

    std::cout << "Part 1: ";
    print(dance("input/input_day16_test.txt"));
    std::cout << std::endl;

    return 0;
} 
