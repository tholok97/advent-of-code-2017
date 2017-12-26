#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <map>

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

//
// Program contains the info associated with a program in part 2
struct Program {
    Registers regs;             // programs own registers
    std::queue<int> received;   // values the program has received from other
    bool waiting;               // is this program waiting?
    int pos;                    // position in instructions
    int numSent;                // number of sent values (for part 2)
};

// read and do next instruction on current.
void doInstruction(Program& current, Program& other, const Instructions& 
        instructions) {

    // make string stream for parsing instruction
    std::istringstream iss(instructions[current.pos]);

    // temps used for reading instructions
    std::string tmpstr; 
    char tmpchar;      

    // we're working with pos. set pos to pos+1 to progress through instructions
    current.pos++;


    // READ instruction name
    iss >> tmpstr;

    // do instruction based on read name
    // (can't switch on strings... so if () else if () else if ()....)
    if (tmpstr == "snd") {

        iss >> tmpstr;                                  // read x
        IntegerType x = parse(tmpstr, current.regs);

        other.received.push(x);                         // send x
        current.numSent++;
    } else if (tmpstr == "set") {

        iss >> tmpchar;                                 // read x
        char x = tmpchar;

        iss >> tmpstr;                                  // read y
        IntegerType y = parse(tmpstr, current.regs);

        current.regs[x] = y;                            // regs[x] = y

    } else if (tmpstr == "add") {

        iss >> tmpchar;                                 // read x
        char x = tmpchar;                                             
                                                                      
        iss >> tmpstr;                                  // read y
        IntegerType y = parse(tmpstr, current.regs);                  
                                                                      
        current.regs[x] += y;                           // regs[x] += y

    } else if (tmpstr == "mul") {

        iss >> tmpchar;                                 // read x
        char x = tmpchar;                                             
                                                                      
        iss >> tmpstr;                                  // read y
        IntegerType y = parse(tmpstr, current.regs);                  
                                                                      
        current.regs[x] *= y;                           // regs[x] *= y

    } else if (tmpstr == "mod") {

        iss >> tmpchar;                                 // read x
        char x = tmpchar;                                             
                                                                      
        iss >> tmpstr;                                  // read y
        IntegerType y = parse(tmpstr, current.regs);                  
                                                                      
        current.regs[x] %= y;                           // regs[x] %= y

    } else if (tmpstr == "rcv") {

        iss >> tmpchar;                                 // read x
        char x = tmpchar;               

        if (current.received.empty()) {                 // if queue empty:
            current.waiting = true;                     //  indicate waiting
            current.pos -= 1;
        } else {                                        // if not empty:
            current.regs[x] = current.received.front(); //  regs[x] = pop()
            current.received.pop();                     
        }

    } else if (tmpstr == "jgz") {

        iss >> tmpstr;                                  // read x
        IntegerType x = parse(tmpstr, current.regs);

        if (x > 0) {                                    // if x > 0
            iss >> tmpstr;
            IntegerType y = parse(tmpstr, current.regs);    // read y

            current.pos += y - 1;                           // jump y positions
        }

    } else {
        std::cout << "ERROR: unknown instruction " << tmpstr << std::endl;
    }
}

// part 2: let two programs work on the instructions until deadlock is reached. 
// The answer is the number of values program 1 sent.
int part2(const Instructions& instructions) {

    // the two programs
    Program p0{{}, std::queue<int>(), false, 0};
    Program p1{{}, std::queue<int>(), false, 0};

    // set initial 'p' value based on program
    p0.regs['p'] = 0;
    p1.regs['p'] = 1;

    // refs used duing iterations to keep track of which is currently being 
    // worked with
    Program& current = p0;
    Program& other = p1;

    // while the program we're working with isn't waiting (current)
    do {

        // do instructions on current until it reaches a waiting state
        while (!current.waiting) {
            doInstruction(current, other, instructions);
        }

        // swap current and other
        std::swap(current, other);

        // update current's waiting state
        if (current.waiting && !current.received.empty()) {
            current.waiting = false;
        }

    } while (!current.waiting);

    return p1.numSent;
}

int main() {

    auto instructions = read("input/input_day18.txt");

    // should be 7112
    std::cout << "Part 2: " << part2(instructions) << std::endl;


    return 0;
} 
