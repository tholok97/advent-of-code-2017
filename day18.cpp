// WIP WIP WIP WIP WIP WIP

#include <iostream>
#include <vector>
#include <memory>
#include <map>

using Registers = std::map<char, int>;

struct Instruction;

struct SetVal;
struct SetChar;
struct AddVal;
struct AddChar;
struct MulVal;
struct MulChar;
struct ModVal;
struct ModChar;

struct SndVal;
struct SndChar;
struct RcvVal;
struct RcvChar;
struct JgzVal;
struct JgzChar;

struct Instruction {
    virtual int go(Registers& regs) = 0;
};

struct SetVal : Instruction {
    char x;
    int y;
    SetVal(char x, int y) { x = x; y = y; }
    virtual int go(Registers& regs) {
        regs[x] = y;
    }
};

struct SetChar : Instruction {
    char x;
    char y;
    SetChar(char x, char y) { x = x; y = y; }
    virtual int go(Registers& regs) {
        regs[x] = regs[y];
    }
};

struct AddVal : Instruction {
    char x;
    int y;
    AddVal(char x, int y) { x = x; y = y; }
    virtual int go(Registers& regs) {
        regs[x] += y;
    }
};

struct AddChar : Instruction {
    char x;
    char y;
    AddChar(char x, char y) { x = x; y = y; }
    virtual int go(Registers& regs) {
        regs[x] += regs[y];
    }
};

struct MulVal : Instruction {
    char x;
    int y;
    MulVal(char x, int y) { x = x; y = y; }
    virtual int go(Registers& regs) {
        regs[y] *= y;
    }
};

struct MulChar : Instruction {
    char x;
    char y;
    MulChar(char x, char y) { x = x; y = y; }
    virtual int go(Registers& regs) {
        regs[x] *= regs[y];
    }
};

struct ModVal : Instruction {
    char x;
    int y;
    ModVal(char x, int y) { x = x; y = y; }
    virtual int go(Registers& regs) {
        regs[y] %= y;
    }
};

struct ModChar : Instruction {
    char x;
    char y;
    ModChar(char x, char y) { x = x; y = y; }
    virtual int go(Registers& regs) {
        regs[x] %= regs[y];
    }
};

struct SndVal {
    int x;
    SndVal(int x) { x = x; }
    virtual int go(Registers& regs) {
        return x;
    }
};

struct SndChar {
    char x;
    SndChar(char x) { x = x; }
    virtual int go(Registers& regs) {
        return regs[x];
    }
};

struct RcvVal {
    int x;
    RcvVal(int x) { x = x; }
    virtual int go(Registers& regs) {

    }
};

struct RcvChar;
struct JgzVal;
struct JgzChar;

int main() {

    std::vector<std::unique_ptr<Instruction>> instructions;

    instructions.push_back(std::make_unique<MulVal>('a', 3));

    Registers regs;
    for (auto& p : instructions) {
        p->go(regs);
    }

    std::cout << "it's working" << std::endl; 

    return 0;
} 
