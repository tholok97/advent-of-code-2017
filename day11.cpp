/*
 * DISCLAIMER: This my solution to day 11 AFTER looking at the reddit 
   discussion. I based my solution on this comment: https://www.reddit.com/r/
   adventofcode/comments/7izym2/2017_day_11_solutions/dr2nuso/
 * My original solution is found in 'day11_old.cpp'
 */

#include <iostream>
#include <array>
#include <vector>
#include <fstream>

// Path is a sequence of steps (each string gives direction of step)
using Path = std::vector<std::string>;

// returns abs of x (duh)
int abs(int x) {
    if (x < 0) {
        x *= -1;
    }

    return x;
}

// print optional text followed by path (for debug purposes)
void print(Path path, std::string text = "") {
    std::cout << text << ": ";
    for (auto step : path)
        std::cout << step << " ";
    std::cout << std::endl;
}

// read steps from file in as a vector of strings
Path readInput(std::string inputFile) {

    std::ifstream ifs(inputFile);
    Path path;                    // resulting path
    std::string step;             // temp variable used to read step from file

    // read character by character into temp, add temp to vec when encounter
    //  comma
    char c;
    while (ifs >> c) {
        if (c == ',') {           // when encounter , -> 'flush' temp to vector
            path.push_back(step);
            step = "";            // reset temp
        } else {
            step += c;            // add character to temp
        }
    }
    path.push_back(step);         // (file doesn't end with comma, flush last
                                  //  step)
    return path;
}

// do steps while keeping track of position in coordinate system. Keep track 
// of minimumDistance to end of path, and maximum distance away from origin 
// along the way
std::pair<int,int> bothParts(Path path) {

    // minLength and furthestLength are values to be returned
    // length is the current length during iterations
    int minLength, furthestLength, length;
    
    // coordinates
    int x = 0;
    int y = 0;
    int z = 0;

    // for each step in the path, do the step and update variables
    for (auto step : path) {
        
        // ( can't switch on strings :(  )
        if (step == "n") {
            y++;
            z--;
        } else if (step == "ne") {
            x++;
            z--;
        } else if (step == "nw") {
            x--;
            y++;
        } else if (step == "s") {
            y--;
            z++;
        } else if (step == "se") {
            y--;
            x++;
        } else if (step == "sw") {
            x--;
            z++;
        } else {
            std::cout << "ERROR: unknown step type: " << step << std::endl;
        }

        length = (abs(x) + abs(y) + abs(z))/2;

        // store maximum length seen so far
        furthestLength = std::max(furthestLength, length);
    }

    // minimum length is the last length
    minLength = length;

    return std::make_pair(minLength, furthestLength);
}

int main() {

    auto path = readInput("input/input_day11.txt");

    auto both = bothParts(path);

    std::cout << "Part 1: " << both.first << std::endl;
    std::cout << "Part 2: " << both.second << std::endl;


    return 0;
} 
