#include <iostream>
#include <utility>
#include <fstream>
#include <sstream>
#include <map>
#include <string>

// return result on evaluating 'lhs' 'op' 'rhs', where op is a valid operator
// ex:                         3     "==" 4      -> would return false
bool checkCondition(auto lhs, std::string op, auto rhs) {

    // can't switch on strings :((((
    if      (op == "==") {  return lhs == rhs; }
    else if (op == "!=") {  return lhs != rhs; }
    else if (op == "<") {   return lhs < rhs; }
    else if (op == ">") {   return lhs > rhs; }
    else if (op == "<=") {  return lhs <= rhs; }
    else if (op == ">=") {  return lhs >= rhs; }
    else {
        std::cout << "ERROR: unknown op: " << op;
        return false;
    }
    
}

// Perform both part 1 and part 2 in one function
// Part 1 will be returned in .first, part 2 in .second
std::pair<int, int> bothParts(std::string inputFile) {

    std::ifstream ifs(inputFile);
    std::map<std::string, int> registers;   // map of register values

    // store largest register value ever (for part 2)
    int largestEver = 0;

    // read instructions from file
    std::string line;
    while (getline(ifs, line)) {

        std::istringstream iss(line); // for simplicities' sake

        // Read instruction line. Structure is (with example):
        // reg operation operationAmount 'if' conditionReg conditionOp conditionAmount;
        // b   inc       5               if   a            >           1
        std::string reg, operation, conditionReg, conditionOp, temp;
        int opertionAmount, conditionAmount;

        iss >> reg >> operation >> opertionAmount >> temp >> 
                conditionReg >> conditionOp >> conditionAmount;

        // if we are going to decrement, just *= -1 the amount to simplify rest 
        //  of code
        if (operation == "dec") {
            opertionAmount *= -1;
        }

        // check conditional (relies on map initializing new entries with 0)
        if (checkCondition(registers[conditionReg], conditionOp, conditionAmount)) {
            registers[reg] += opertionAmount;
            largestEver = std::max(registers[reg], largestEver);    // update largestEver
        }
    }
    
    // find largest value of a register: (loop through and find largest)
    auto largest = registers.begin()->second;
    for (const auto& pair : registers) {
        largest = std::max(pair.second, largest);
    }

    // return largests
    return std::make_pair(largest,largestEver);
}

int main() {

    // .first gies part 1, .second gives part 2
    auto results = bothParts("input/input_day8.txt");

    std::cout << "Part 1:" << results.first << std::endl;
    std::cout << "Part 2:" << results.second << std::endl;

    return 0;
} 
