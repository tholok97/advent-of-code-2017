#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <sstream>

using Instructions = std::vector<std::string>;

Instructions read(std::string inputFile) {

    std::ifstream ifs(inputFile);

    Instructions instructions;

    std::string line;
    while (getline(ifs, line)) {
        instructions.push_back(line);
    }

    return instructions;
}

using Registers = std::map<char, long long int>;

bool isInt(std::string str) {
    for (const char c : str) {
        if ((c < '0' || c > '9') && c != '-') {
            return false;
        }
    }
    return true;
}

long long int parse(std::string str, Registers& regs) {
    if (isInt(str)) {
        return std::stoi(str);
    } else {
        return regs[str[0]];
    }
}

long long int part1(std::string inputFile) {

    auto instructions = read(inputFile);

    Registers regs;

    bool recoverReached = false;

    std::string tmpstr;
    char tmpchar;

    long long int lastFreq = -1;

    int i = 0;
    while (!recoverReached) {

        std::cout << i << ": ";

        std::istringstream iss(instructions[i]);

        iss >> tmpstr;

        //  (  can't switch on strings :((  )
        if          (tmpstr == "snd") {
            iss >> tmpstr;
            long long int x = parse(tmpstr, regs);
            lastFreq = x;

            std::cout << "snd " << x;

        } else if   (tmpstr == "set") {

            iss >> tmpchar;
            char x = tmpchar;
            
            iss >> tmpstr;
            long long int y = parse(tmpstr, regs);

            regs[x] = y;

            std::cout << "set " << x << " " << y;

        } else if   (tmpstr == "add") {

            iss >> tmpchar;
            char x = tmpchar;
            
            iss >> tmpstr;
            long long int y = parse(tmpstr, regs);

            regs[x] += y;

            std::cout << "add " << x << " " << y;


        } else if   (tmpstr == "mul") {

            iss >> tmpchar;
            char x = tmpchar;
            
            iss >> tmpstr;
            long long int y = parse(tmpstr, regs);

            regs[x] *= y;

            std::cout << "mul " << x << " " << y;

        } else if   (tmpstr == "mod") {

            iss >> tmpchar;
            char x = tmpchar;
            
            iss >> tmpstr;
            long long int y = parse(tmpstr, regs);

            regs[x] %= y;

            std::cout << "mod " << x << " " << y;

        } else if   (tmpstr == "rcv") {

            iss >> tmpstr;
            long long int x = parse(tmpstr, regs);

            if (x) {
                recoverReached = true;
            }

            std::cout << "rcv " << x;

        } else if   (tmpstr == "jgz") {

            iss >> tmpstr;
            long long int x = parse(tmpstr, regs);

            std::cout << "jgz " << x;

            if (x > 0) {
                iss >> tmpstr;
                long long int y = parse(tmpstr, regs);

                i += y - 1;

                std::cout << " " << y;
            }

        } else {
            std::cout << "ERROR: unknown instruction " << tmpstr << std::endl;
        }

        std::cout << "      a: " << regs['a'] << std::endl;

        i += 1;
    }

    return lastFreq;
}

int main() {

    std::cout << "Part 1: " << part1("input/input_day18.txt") << std::endl;

    return 0;
} 
