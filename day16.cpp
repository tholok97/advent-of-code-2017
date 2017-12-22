#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <vector>

// abcdef 3
// x
//   x
void spin(std::vector<char>& programs, int length) {

    std::rotate(programs.begin(), programs.begin() + programs.size() - length, 
            programs.end());
}

void exchange(std::vector<char>& programs, int pos1, int pos2) {
    std::swap(programs[pos1], programs[pos2]);
}

void partner(std::vector<char>& programs, char c1, char c2) {
    int pos1, pos2;
    pos1 = std::find(programs.begin(), programs.end(), c1) - programs.begin();
    pos2 = std::find(programs.begin(), programs.end(), c2) - programs.begin();

    exchange(programs, pos1, pos2);
}

struct Move {
    virtual void doMove(std::vector<char>& programs);
};

struct Spin : Move {
    int length;
    virtual void doMove(std::vector<char>& programs) {
        spin(programs, length);
    }
};

struct Exchange : Move {
    int pos1;
    int pos2;
    virtual void doMove(std::vector<char>& programs) {
        exchange(programs, pos1, pos2);
    }
};

struct Partner : Move {
    char c1;
    char c2;
    virtual void doMove(std::vector<char>& programs) {
        partner(programs, c1, c2);
    }
};




std::vector<char> dance(std::vector<char> programs, std::string danceStr) {

    std::istringstream iss(danceStr);

    char move;
    char dummyChar;
    while (iss >> move) {
        switch(move) {
        case 's': 
            int length;
            iss >> length >> dummyChar;
            spin(programs, length);
            break;
        case 'x': 
            int pos1, pos2;
            iss >> pos1 >> dummyChar >> pos2 >> dummyChar;
            exchange(programs, pos1, pos2);
            break;
        case 'p': 
            char c1, c2;
            iss >> c1 >> dummyChar >> c2 >> dummyChar;
            partner(programs, c1, c2);
            break;
        default: 
            std::cout << "ERROR! We don't know the move: " << move << std::endl;
        }
    }


    return programs;
}

std::vector<char> superdance(std::vector<char> programs, std::string danceFile) {

    for (unsigned long long int i = 0; i < 1000000000; ++i) {
        if (i % 100 == 0) std::cout << i << '\n';
        programs = dance(programs, danceFile);
    }
    
    return programs;
}

void print(std::vector<char> d) {
    for (char c : d)
        std::cout << c;
    std::cout << std::endl;
}

int main() {

    // init programs as vector of chars from 'a' to 'p'
    std::vector<char> programs;
    for (char c = 'a'; c <= 'p'; c++)
        programs.push_back(c);

    std::string danceStr;
    std::ifstream ifs("input/input_day16.txt");

    ifs >> danceStr;

    std::cout << "Part 1: ";
    print(dance(programs, danceStr));
    std::cout << std::endl;

    std::cout << "Part 2: ";
    print(superdance(programs, danceStr));
    std::cout << std::endl;

    return 0;
} 
