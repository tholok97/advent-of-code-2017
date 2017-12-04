#include <iostream>
#include <algorithm>
#include <sstream>
#include <set>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::string> readInput(std::string inputFile) {

    std::vector<std::string> input;
    std::ifstream ifs(inputFile);

    std::string line;
    while (std::getline(ifs, line)) {
        input.push_back(line);
    }

    return input;
}

bool valid(std::string line) {

    std::set<std::string> seen;
    std::istringstream iss(line);
    std::string word;

    while (iss >> word) {

        if (seen.find(word) == seen.end()) {
            seen.insert(word);
        } else {
            return false;
        }
    }

    return true;
}

bool valid2(std::string line) {

    std::set<std::string> seen;
    std::istringstream iss(line);
    std::string word;

    while (iss >> word) {

        std::string sorted = word;
        std::sort(sorted.begin(), sorted.end());

        if (seen.find(sorted) == seen.end()) {
            seen.insert(sorted);
        } else {
            return false;
        }
    }

    return true;
}

int part1(std::vector<std::string> input) {
    
    int numValid = 0;
    for (std::string line : input) {
        if (valid(line)) {
            numValid++;
        } 
    }

    return numValid;
}

int part2(std::vector<std::string> input) {

    int numValid = 0;
    for (std::string line : input) {
        if (valid2(line)) {
            numValid++;
        } 
    }

    return numValid;

}

int main() {

    // ..input relative to repo root
    auto input = readInput("day4/input.txt");

    std::cout << "Part 1: " << part1(input) << std::endl;
    std::cout << "Part 2: " << part2(input) << std::endl;

    return 0;
} 
