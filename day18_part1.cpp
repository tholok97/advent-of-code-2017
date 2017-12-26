#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <sstream>

// huge integer type for registers
using IntegerType = long long int;

// registers are implemented as map from char to IntegerType
using Registers = std::map<char, IntegerType>;

// Instructions are stored as vector strings (strings cause parsing the 
// instrucions isn't the bottleneck here)
using Instructions = std::vector<std::string>;

// read instructions from file
Instructions read(std::string inputFile) {

    std::ifstream ifs(inputFile);

    Instructions instructions;

    std::string line;
    while (getline(ifs, line)) {
        instructions.push_back(line);
    }

    return instructions;
}

// does this string represent an int?
bool isInt(std::string str) {
    for (const char c : str) {
        if ((c < '0' || c > '9') && c != '-') {
            return false;
        }
    }
    return true;
}

// parse a string that is EITHER a char name of a registry (in which case return
// the value of that registry), OR simply a number (in which case return that 
// number)
IntegerType parse(std::string str, Registers& regs) {
    if (isInt(str)) {
        return std::stoi(str);
    } else {
        return regs[str[0]];
    }
}

// part 1: do instructions, store frequencies sent by snd, when first rcv is 
// encountered return last sent frequency
IntegerType part1(const Instructions& instructions) {

    Registers regs;         // registers

    // temps used for reading instructions
    std::string tmpstr;
    char tmpchar;

    // variable that record last sent (snd) frequency
    IntegerType lastFreq = -1;

    // boolean that indicates if the first rcv has been found
    bool recoverReached = false;

    // pos in instructions
    int pos = 0;

    // while we haven't seen a rcv statement, do next instruction
    while (!recoverReached) {

        // string stream of current instruction
        std::istringstream iss(instructions[pos]);

        // read instruction name
        iss >> tmpstr;

        // do the instruction indicated by the instruction name
        //  (  can't switch on strings :((  )
        if (tmpstr == "snd") {

            iss >> tmpstr;                          // read x
            IntegerType x = parse(tmpstr, regs);

            lastFreq = x;                           // rememeber x

        } else if (tmpstr == "set") {

            iss >> tmpchar;                         // read x
            char x = tmpchar;
            
            iss >> tmpstr;                          // read y
            IntegerType y = parse(tmpstr, regs);

            regs[x] = y;

        } else if (tmpstr == "add") {

            iss >> tmpchar;                         // read x
            char x = tmpchar;                                 
                                                              
            iss >> tmpstr;                          // read y
            IntegerType y = parse(tmpstr, regs);

            regs[x] += y;

        } else if (tmpstr == "mul") {

            iss >> tmpchar;                         // read x
            char x = tmpchar;                                 
                                                              
            iss >> tmpstr;                          // read y
            IntegerType y = parse(tmpstr, regs);

            regs[x] *= y;

        } else if (tmpstr == "mod") {

            iss >> tmpchar;                         // read x
            char x = tmpchar;                                 
                                                              
            iss >> tmpstr;                          // read y
            IntegerType y = parse(tmpstr, regs);

            regs[x] %= y;

        } else if (tmpstr == "rcv") {

            iss >> tmpstr;                          // read x
            IntegerType x = parse(tmpstr, regs);

            if (x) {                                // if x > 0: 
                recoverReached = true;              //  indicate that we've 
            }                                       //  reached a rcv (loop
                                                    //  should terminate)
        } else if (tmpstr == "jgz") {

            iss >> tmpstr;                          // read x
            IntegerType x = parse(tmpstr, regs);

            if (x > 0) {                            // if x > 0:
                iss >> tmpstr;                      //  read y
                IntegerType y = parse(tmpstr, regs);

                pos += y - 1;                       //  jump by y

            }

        } else {
            std::cout << "ERROR: unknown instruction " << tmpstr << std::endl;
        }

        // progress to next instruction
        pos++;
    }

    return lastFreq;
}

int main() {

    auto instructions = read("input/input_day18.txt");

    // should be 3188
    std::cout << "Part 1: " << part1(instructions) << std::endl;

    return 0;
} 
