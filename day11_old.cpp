/*
 * This was my first attempt. A (much faster) second attempt is found 
   in 'day11.cpp'. 
 * I didn't find an easy way to do it by coordinates at first (which is what 
   'day11.cpp' does), so I made ended up solving it by optimalizing the path 
   given, and finding the length of the optimalized version. 
 * The meat of this solution is the 'shorten' function, that given a path gives 
   back an optimal version (minimum length).
 * Part 1 works fine. Part 2 takes several minutes...
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

// Tranformation in path. Occurrances of first + second should be replaced
//  with result (to shorten)
struct Transformation {
    std::string first;
    std::string second;
    std::string result;
};

// tranform path by t. Return reduced vector as .first, and vector of new 
//  values as .second
std::pair<Path, Path> transformReplace(Path path, Transformation t) {

    Path toadd;     // values to add as a result of transform

    // tranform until can't find another pair to tranform
    int firstIndex, secondIndex;
    do {
        firstIndex = -1;
        secondIndex = -1;

        // seek after pair to transform
        for (int i = 0; i < path.size(); ++i) {
            if (firstIndex != -1) {
                if (path[i] == t.second) {
                    secondIndex = i;
                    break;
                }
            } else {
                if (path[i] == t.first) {
                    firstIndex = i; 
                }
            }
        }

        // if found pair -> reduce from path and add result to toadd
        if (firstIndex != -1 && secondIndex != -1) {
            path.erase(path.begin()+firstIndex);
            path.erase(path.begin()+secondIndex-1);
            if (t.result != "") {
                toadd.push_back(t.result);
            }
        }
    } while (firstIndex != -1 && secondIndex != -1);

    return std::make_pair(path, toadd);
}

// Shorten path by applying tranformations
Path shorten(Path path) {

    // transformations that apply to hex paths (found these with pen and paper)
    // Form: { X, Y, Z } -> X and Y found in a path should be replaced by Y
    static std::array<Transformation, 7> transforms = {{
        {"n", "s", ""},
        {"ne", "nw", "n"},
        {"se", "sw", "s"},
        {"n", "se", "ne"},
        {"n", "sw", "nw"},
        {"s", "nw", "sw"},
        {"s", "ne", "se"}
    }};


    // apply transformations (both {first, second} and {second, first})
    Path toadd;
    for (auto t : transforms) {

        // do transform. store reduced and toadd
        auto result = transformReplace(path, t);
        path = result.first;
        toadd.insert(toadd.end(), result.second.begin(), result.second.end());

        // do other way around
        std::swap(t.first, t.second);

        // do transform. store reduced and toadd
        result = transformReplace(path, t);
        path = result.first;
        toadd.insert(toadd.end(), result.second.begin(), result.second.end());
        path.insert(path.end(), toadd.begin(), toadd.end());

        // add toadd back to the path (not storing toadd seperately caused 
        //  problems.. I don't understand why tbh)
        toadd.erase(toadd.begin(), toadd.end());
    }

    return path;
}

// find length of path
int lengthOfPath(Path path) {

    // count positions in three 'dimensions'
    int n = 0;
    int ne = 0;
    int nw = 0; 

    // for each step -> go in that direction
    for (auto step : path) {
        
        // (can't switch on strings :( )
        if        (step == "n") {   n++;
        } else if (step == "s") {   n--;
        } else if (step == "ne") {  ne++;
        } else if (step == "sw") {  ne--;
        } else if (step == "nw") {  nw++;
        } else if (step == "se") {  nw--;
        } else {
            std::cout << "malformed step: " << step << std::endl;
        }
    }

    // length is sum of abs of position
    return abs(n) + abs(ne) + abs(nw);
}

// part 1: find distance from origin
int part1(Path path) {
    path = shorten(path);
    return lengthOfPath(path);
}

// part 2: find max distance from origin during path 
// (WARNING: slow. takes a while)
int part2(Path path) {

    int max = 0;            // current max distance
    int counter = 0;        // used for debug output

    // find length of shortest path to the end of path, [update max, ] 
    //  reduce path by one, repeat
    while (path.size() > 0) {
        int dist = part1(path);         // shortest distance to end of path
        max = std::max(dist, max);      // [update max]
        path.pop_back();                // reduce path by one

        // print debug info every 100'th iteration
        counter++;
        if (counter >= 100) {
            counter = 0;
            std::cout << "path.size(): " << path.size() << ", max: " << max << std::endl;
        }
    }

    return max;
}

int main() {

    auto path = readInput("input/input_day11.txt");

    std::cout << "Part 1: " << part1(path) << std::endl;

    std::cout << "WARNING! Part 2 takes several minutes. "
            "Debug info will be printed along the way." << std::endl;

    std::cout << "Part 2: " << part2(path) << std::endl;


    return 0;
} 
