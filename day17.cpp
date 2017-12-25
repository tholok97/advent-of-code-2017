/*
 * Part 1 I solved using the specialized circular buffer implementation below
 * Part 2 I solved using algmet
 */

#include <iostream>
#include <vector>

// Circular buffer used for part 1. Keeps track of next position to insert 
// value in. This position can be advanced with the forward function. The value 
// function gives the value at the current position
// (this thing could easily be templated, but didn't see the need)
class SpinlockBuffer {
private:
    std::vector<int> vec;           // uses vector of ints internally
    decltype(vec.begin()) it;       // iterator holding current position

public:
    SpinlockBuffer(): vec({0}), it(vec.begin()) { } 

    // insert value AFTER current position
    void insert(int val) {
        ++it;                           
        it = vec.insert(it, val);
        
    }

    // advance the current position by n. wraps around
    void forward(int n) {

        for (int i = 0; i < n; ++i) {
            ++it;
            if (it == vec.end()) {      // if at end. wrap around
                it = vec.begin();
            }
        }
    }

    // return value of current position
    int value() {
        return *it;
    }

    // print the thing (for debug)
    void print() {
        for (auto val : vec) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
};

// part 1: do the spinlock algorithm, and return the value after 2017
int part1(int stepSize) {
    
    SpinlockBuffer sb;

    for (int i = 1; i <= 2017; ++i) {
        sb.forward(stepSize);
        sb.insert(i);
    }

    sb.forward(1);      // advance by one to get value after 2017

    return sb.value();
}

// part 2: do the spinlock algorithm ALOT of times, and we only care about 
// the value after 0. Solution in part 1 would take forever, and eat up all my 
// memory, so solved it with some clever algmet instead
int part2(int stepSize) {

    int pos = 0;                                // current position in 'buffer'
    unsigned long int numInsertions = 50000000; // number of 'insertions' to do
    int size = 1;                               // size of 'buffer'
    int result;                                 // stores result

    // for each i to be 'inserted', calculate the position it would be inserted 
    // at, and if it's the position we care about: store it (if we don't care 
    // about it, do nothing)
    for (int i = 1; i <= numInsertions; ++i) {
        pos = (pos + stepSize) % size;          // advance position
        pos++;                                  // insertion happens at pos+1
        size++;                                 // insertion happened. size++

        // if this is a pos we care about -> store the 'inserted' value
        if (pos == 1) {
            result = i; 
        }
    }

    return result;
}

int main() {

    int puzzleInput = 376;

    std::cout << "Part 1: " << part1(puzzleInput) << std::endl;
    std::cout << "Part 2: " << part2(puzzleInput) << std::endl;

    return 0;
} 
