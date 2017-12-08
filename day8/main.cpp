#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>

void p(std::string text) {
    std::cout << text << std::endl;
}


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

auto part1(std::string inputFile) {

    std::ifstream ifs(inputFile);
    std::map<std::string, int> registers;

    // read instructions from file
    std::string line;
    while (getline(ifs, line)) {

        std::istringstream iss(line);

        // Read instruction line. Structure is: (with example)
        // reg operation operationAmount 'if' conditionReg conditionOp conditionAmount;
        // b   inc       5               if   a            >           1
        std::string reg, operation, conditionReg, conditionOp, temp;
        int opertionAmount, conditionAmount;

        iss >> reg >> operation >> opertionAmount >> temp >> 
                conditionReg >> conditionOp >> conditionAmount;

//        std::cout << reg << " "<< operation << " "<< opertionAmount << " if " << 
//                conditionReg << " "<< conditionOp << " "<< 
//                conditionAmount << std::endl;

        // if we are going to decrement, just *= -1 the amount to simplify rest 
        //  of code
        if (operation == "dec") {
            opertionAmount *= 1;
        }

        // check conditional (relies on map initializing new entries with 0)
        if (checkCondition(registers[conditionReg], conditionOp, conditionAmount)) {
            registers[reg] += opertionAmount;
        }
    }
    
    // find largest value of a register: (loop through and find largest)
    auto largest = registers.begin()->second;
    std::cout << "initial largest " << largest << std::endl;
    for (const auto& pair : registers) {
        std::cout << pair.first << '\t' << pair.second << " ? " << largest << std::endl;
        largest = std::max(pair.second, largest);
    }

    // return largest
    return largest;
}

int main() {


    p("Test: " + std::to_string(part1("input/input_day8_test.txt")));
    p("Part 1:" + std::to_string(part1("input/input_day8.txt")));

    return 0;
} 
