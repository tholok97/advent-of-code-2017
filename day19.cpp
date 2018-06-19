/* THE WAY I UNDERSTAND THE TASK:

GIVEN:

     |
     |  +--+
     A  |  C
 F---|----E|--+
     |  |  |  D
     +B-+  +--+

THE "PACKET" STARTS ABOVE A AND TRAVELS FOLLOWING THE LINE. WHAT LETTERS DOES IT SEE ALONG IT'S PATH (TO F)? 

SOLUTION IN THIS CASE: ABCDEF

 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using Grid = std::vector<std::vector<char>>;

/**
 * Parse file at 'inputFile' into Grid and return
 */
Grid parseInput(std::string inputFile) {

    Grid grid;

    // read input from file into 'input' 
    std::ifstream ifs(inputFile);

    // for each line in file
    std::string line;
    while (getline(ifs, line)) {

        // make new subvector and fill with string
        grid.push_back(std::vector<char>(line.begin(), line.end()));
    }

    return grid;
}

/**
 * Stores position in (x,y)
 */
struct Position {
    int x;
    int y;
};

/**
 * Solves part 1 of puzzle using given grid. Returns visited characters
 */
std::string part1(const Grid& grid) {

    // initial position of packet set to (0,0).
    Position pos{0,0};

    // seek until found starting position of packet (line at top edge of grid)
    while (grid[pos.y][pos.x] != '|') {

        // seek one x to the right
        ++pos.x;
    }

    // (pos is now correctly positioned at start of packet path)
    
    enum Direction { UP, RIGHT, DOWN, LEFT } dir = Direction::DOWN;

    //while (true) {

        char currentChar = grid[pos.y][pos.x];

        // switch on dir
        // DOWN:
        //  IF NEXT IS |, CONTINUE
        //  IF NEXT IS CHARACTER, CONTINUE
        //  IF NEXT IS +, EXECUTE INTERSECTION CODE
        //  IF NEXT IS -, EXECUTE CROSSOVER CODE

    //}



    return "";
}

int main() {

    Grid grid = parseInput("input/input_day19_test.txt");

    std::cout << "Part 1: " << part1(grid) << std::endl;

    return 0;
}
