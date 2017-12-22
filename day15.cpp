#include <iostream>

struct Generator {
    unsigned long int factor;
    unsigned long int previous;
    int multipleOf;
};

// generate next previous
Generator gen(Generator generator) {
    generator.previous = (generator.previous * generator.factor) % 2147483647;
    return generator;
}

// generate until multiple of 'multipleOf'
Generator gen2(Generator generator) {
    do {
        generator.previous = (generator.previous * generator.factor) % 2147483647;
    } while (generator.previous % generator.multipleOf != 0);

    return generator;
}

// judge will approve if the previous values' last 16 bits match
bool judgeApproves(Generator a, Generator b) {
    return (a.previous & 65535) == (b.previous & 65535);
}

// part 1: count number of times generator pairs match. judge does 40 million 
// iterations
int part1(int initialA, int initialB) {
   
    Generator a{16807, initialA};
    Generator b{48271, initialB};

    int num = 0;
    for (unsigned long int i = 0; i < 40000000; ++i) {
        a = gen(a);
        b = gen(b);

        if (judgeApproves(a, b)) {
            ++num;
        }
    }

    return num;
}

// part 2: count number of times generator pairs match. judge is impatient: 
// will only do 5 million iterations
int part2(int initialA, int initialB) {

    Generator a{16807, initialA, 4};
    Generator b{48271, initialB, 8};

    int num = 0;
    for (unsigned long int i = 0; i < 5000000; ++i) {
        a = gen2(a);
        b = gen2(b);

        if (judgeApproves(a, b)) {
            ++num;
        }
    }

    return num;
}

int main() {

    std::cout << "Part 1: " << part1(722, 354) << std::endl;
    std::cout << "Part 2: " << part2(722, 354) << std::endl;

    return 0;
} 
