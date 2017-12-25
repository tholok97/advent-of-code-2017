#include <iostream>
#include <vector>

class SpinlockBuffer {
private:
    std::vector<int> vec;
    decltype(vec.begin()) it;

public:
    SpinlockBuffer(): vec({0}), it(vec.begin()) { }
    void insert(int val) {
        ++it;
        it = vec.insert(it, val);
        
    }
    void forward(int n) {
        while (n > vec.size()) {
            n -= vec.size();
        }
        for (int i = 0; i < n; ++i) {
            ++it;
            if (it == vec.end()) {
                it = vec.begin();
            }
        }
    }
    int value() {
        return *it;
    }
    void print() {
        for (auto val : vec) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
};

int part1(int stepSize) {
    
    SpinlockBuffer sb;

    for (int i = 1; i <= 2017; ++i) {
        sb.forward(stepSize);
        sb.insert(i);
    }

    sb.forward(1);

    return sb.value();
}

/*
int part2(int stepSize) {

    SpinlockBuffer sb;

    unsigned long int last = 50000000;

    for (int i = 1; i <= last; ++i) {
        sb.forward(stepSize);
        sb.insert(i);

        if (i % 10000 == 0) 
            std::cout << (last - i) << std::endl;
    }

    while (sb.value() != 0) {
        sb.forward(1);
    }

    sb.forward(1);

    return sb.value();
}
*/

int part2(int stepSize) {

    int pos = 0;
    unsigned long int numInsertions = 50000000;
    int size = 1;
    int result;

    for (int i = 1; i <= numInsertions; ++i) {
        pos = (pos + stepSize) % size;
        pos++;
        size++;

        if (pos == 1) {
            result = i; 
        }
    }

    return result;
}

int main() {

    int input = 376;

    std::cout << "Part 1: " << part1(input) << std::endl;
    std::cout << "Part 2: " << part2(input) << std::endl;

    return 0;
} 
