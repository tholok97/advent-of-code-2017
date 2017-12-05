#include <iostream>
#include <vector>
#include <fstream>

std::vector<int> readInput(std::string inputFile) {

    std::vector<int> offsets;
    std::ifstream ifs(inputFile);

    int offset;
    while (ifs >> offset) {
        offsets.push_back(offset);
    }
    
    return offsets;
}

int part1(std::vector<int> offsets) {

    int pos = 0;
    int steps = 0;

    while (pos >= 0 && pos < offsets.size()) {
        pos += offsets[pos]++;
        steps++;
    }

    return steps;
}

int part2(std::vector<int> offsets) {

    int pos = 0;
    int steps = 0;

    while (pos >= 0 && pos < offsets.size()) {

        // part 2 rule: >= 3: --, otherwise ++
        pos += offsets[pos] >= 3 ? offsets[pos]-- : offsets[pos]++;
        ++steps;
    }

    return steps;
}

int main() {

    // get vector of offsets
    auto offsets = readInput("day5/input.txt");  

    // do parts
    std::cout << "Part 1: " << part1(offsets) << std::endl;
    std::cout << "Part 2: " << part2(offsets) << std::endl;

    return 0;
} 
