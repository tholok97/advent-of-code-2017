#include <iostream>
#include <fstream>

// do both part 1 and 2 in one function. .first will be answer to part 1 and
//  .second will be answer to part 2
std::pair<int,int> bothParts(std::string inputFile) {

    std::ifstream ifs(inputFile);

    int score = 0;              // current score total (part 1)
    int garbageCount = 0;       // how much garbage we've encountered (part 2)
    int groupsDeep = 0;         // how many groups deep are we? ({{{ -> 3 deep)
    bool ignoreNext = false;    // should next char be ignored?
    bool inGarbage = false;     // are we currently in garbage

    // read while there is stuff in the "stream"
    char c;
    while (ifs >> c) {

        // if we just read a '!', ignore this character completely
        if (ignoreNext) {
            ignoreNext = false;
            continue;
        }

        // if we're currenly not in garbage (we haven't encountered a '<')
        if (!inGarbage) {

            // we are not in garbage: check for group chars or start 
            //  of garbage
            switch(c) {
                case '{':
                    groupsDeep++;
                    score += groupsDeep;
                    break;
                case '}': 
                    groupsDeep--;     
                    break;
                case '<': 
                    inGarbage = true; 
                    break;
            }
        } else {

            // we are in garbage: check for end of garbage or ignores
            switch(c) {
                case '>': 
                    inGarbage = false; 
                    break;
                case '!': 
                    ignoreNext = true; 
                    break;
                default: 
                    garbageCount++;
            }
        }
    }

    // return score and garbageCount (part 1 and 2)
    return std::make_pair(score, garbageCount);
}

int main() {

    auto solutions = bothParts("input/input_day9.txt");

    std::cout << "Part 1: " << solutions.first << std::endl;
    std::cout << "Part 2: " << solutions.second << std::endl;

    return 0;
} 
