#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

// represents the state of banks. typdefed cause use it all the time
using Banks = std::vector<int>;

int part1(Banks banks) {

    std::set<Banks> seen;   // the states we've seen so far
    int redists = 0;        // number of redistrobutions so far
    
    // do redistribute thing until encounter seen state
    do {
        redists++;

        // add to seen
        seen.insert(banks);

        // choose biggest index
        int indexBiggest = std::distance(banks.begin(), 
                std::max_element(banks.begin(), banks.end()));

        // get value of biggest 
        int valueBiggest = banks[indexBiggest];

        // redistribute
        banks[indexBiggest] = 0;
        for (int i = 0; i < valueBiggest; ++i) {
            int redistributeIndex = (indexBiggest+1+i) % banks.size();
            banks[redistributeIndex]++;
        }
        
    } while (seen.find(banks) == seen.end());   

    return redists;
}

int part2(Banks banks) {

    std::set<Banks> seen;   // the states we've seen so far
    int redists = 0;        // number of redistrobutions to get from first 
                            //  seen state back to same state
    Banks seenBanks; // first seen state
    
    // do redistribute thing until encounter seen state (LIKE IN PART 1)
    do {
        // add to seen
        seen.insert(banks);

        // choose biggest index
        int indexBiggest = std::distance(banks.begin(), 
                std::max_element(banks.begin(), banks.end()));

        // get value of biggest 
        int valueBiggest = banks[indexBiggest];

        // redistribute
        
        banks[indexBiggest] = 0;

        for (int i = 0; i < valueBiggest; ++i) {
            int redistributeIndex = (indexBiggest+1+i) % banks.size();
            banks[redistributeIndex]++;
        }

    } while (seen.find(banks) == seen.end());

    // store state of first seen state
    seenBanks = banks;

    // do redistribute thing again until encounter the first seen state again
    do {
        redists++;

        // choose biggest index
        int indexBiggest = std::distance(banks.begin(), 
                std::max_element(banks.begin(), banks.end()));

        // get value of biggest 
        int valueBiggest = banks[indexBiggest];

        // redistribute
        
        banks[indexBiggest] = 0;

        for (int i = 0; i < valueBiggest; ++i) {
            int redistributeIndex = (indexBiggest+1+i) % banks.size();
            banks[redistributeIndex]++;
        }

    } while (banks != seenBanks);

    return redists;
}

int main() {

    Banks input = {14,0,15,12,11,11,3,5,1,6,8,4,9,1,8,4};

    std::cout << "Part 1: " << part1(input) << std::endl;
    std::cout << "Part 2: " << part2(input) << std::endl;

    return 0;
} 
