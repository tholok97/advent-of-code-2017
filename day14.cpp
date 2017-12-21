#include <iostream>
#include <stack>
#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

//-------------------------------- FROM DAY 10 ---------------------------------


// return new vector with positions from startpos to startpos+length reversed
// (circular / wraps around)
std::vector<int> reverse(std::vector<int> list, int startPos, int length) {

    // early return if invalid input
    if (length > list.size() || startPos >= list.size()) {
        std::cout << "ERROR: Invalid input to reverse function" << std::endl;
        return list;
    }

    // make list of indexes to reverse
    std::vector<int> revIndexes;
    for (int i = 0; i < length; ++i) {
        int index = (startPos + i) % list.size();
        revIndexes.push_back(index);
    }

    // fetch values in indexes into temp vector
    std::vector<int> revValues;
    for (auto i : revIndexes)
        revValues.push_back(list[i]);

    // reverse temp vector
    std::reverse(revValues.begin(), revValues.end());

    // insert reversed values in temp vector back to list
    int i = 0;
    for (auto rev : revValues) {
        list[revIndexes[i]] = rev; 
        ++i;
    }

    return list;
}

// do knot hash as described in the text 'rounds' times
std::vector<int> knotHashRounds(std::vector<int> lengths, int listSize, int rounds) {

    std::vector<int> list;

    // fill list with values 0..listSize
    for (int i = 0; i < listSize; ++i)
        list.push_back(i); 

    // do 'rounds' number of knot hashes
    int currPos = 0;
    int skip = 0;
    for (int i = 0; i < rounds; ++i) {
        for (auto l : lengths) {
            
            list = reverse(list, currPos, l);
            currPos += l + skip;
            ++skip;

            currPos = currPos % list.size();
        }
    }

    return list;
}

// put each character in a string in an ivec as ascii
std::vector<int> strtoasciivec(std::string input) {
    
    std::vector<int> asciis;

    for (char c : input)
        asciis.push_back(c);

    return asciis;
}

// parse string of comma-separated int's to vector of ints
std::vector<int> strtoivec(std::string input) {

    std::vector<int> lengths;
    std::istringstream iss(input);      // use iss to parse

    int num;
    char comma;
    while (iss >> num) {            // read int
        lengths.push_back(num);     // push it back
        iss >> comma;               // ignore comma
    }

    return lengths;
}

// append mandatory knot hash suffix to list (salting (?))
std::vector<int> applyKnotHashSuffix(std::vector<int> list) {

    list.push_back(17);
    list.push_back(31);
    list.push_back(73);
    list.push_back(47);
    list.push_back(23);

    return list;
}

// make sparse hash dense: For each block of 16 integers in the sparseHash, xor 
//  them together into one int. Returned denseHash list will be 16 long (there 
//  are 16 groups of 16 in the sparseHash)
std::vector<int> densify(std::vector<int> sparseHash) {
    
    std::vector<int> denseHash;

    for (int i = 0; i < 16; ++i) {                  // for each group of 16:
        int xored = sparseHash[i*16];               // xor the values together
        for (int j = i*16+1; j < i*16 + 16; ++j) {
            xored ^= sparseHash[j];
        }
        denseHash.push_back(xored);                 // and add xored to new vec
    }

    return denseHash;
}


// Turn int into hex string with no fewer than minDigits digits (0's will 
//  be prepended)
std::string toHex(int i, int minDigits) {
    
    std::string hexStr;
    std::vector<int> hexNums;

    while (i > 0) {                 // turn int into list of hex numbers
        int mod = i % 16;
        hexNums.push_back(mod);
        i /= 16;
    }

    while (hexNums.size() < minDigits)  // add 0's as per minDigits
        hexNums.push_back(0);

    // reverse so string is in the correct order
    std::reverse(hexNums.begin(), hexNums.end());   

    // for each hex digit -> turn it into a hex char (1, 2,..9,a,b,..f)
    for (int num : hexNums) {
        std::string hex;
        if (num > 9) {
            num -= 9;
            hex = 'a'+char(num)-1;
        } else {
            hex = std::to_string(num);
        }

        hexStr.append(hex);
    }

    return hexStr;
}

int hexToInt(char c) {
    int num;
    if (c >= 'a') {
        num = c - 'a' + 10;
    } else {
        num = c - '0';
    }

    return num;
}

std::array<bool, 4> toBin(int num) {

    std::array<bool, 4> bits;

    for (int i = 3; i >= 0; --i) {
        bits[i] = num % 2;
        num /= 2;
    }
    
    return bits;
}

std::array<bool, 128> hashToBin(std::string hash) {

    std::array<bool, 128> bits;

    int pos = 0;
    for (char c : hash) {
        auto cbits = toBin(hexToInt(c));
        for (int i = 0; i < 4; ++i) {
            bits[pos++] = cbits[i];
        }
    }

    return bits;
}

// do knot hash on input string. Returns hash string
std::string knotHash(std::string input) {
    
    // build lengths from input
    auto lengths = applyKnotHashSuffix(strtoasciivec(input));

    // build sparse from lengths
    auto sparseHash = knotHashRounds(lengths, 256, 64);

    // build dense from sparse
    auto denseHash = densify(sparseHash);

    // build hash from denseHash (turn into hex string)
    std::string hash;
    for (int i : denseHash) {
        hash.append(toHex(i, 2));
    }

    return hash;
}

//------------------------------- NEW IN DAY 14 --------------------------------

// Grid is 128x128 bool values
using Grid = std::array<std::array<bool, 128>, 128>;

// find number of regions in grid. A region is a collection of true values in 
// the grid that neighbor each other. See aoc description for more detail 
// Ex:
// 1 1 0 0
// 1 0 0 1
// 0 0 0 1
//
// ^ this grid has 2 regions
int numRegions(Grid grid) {

    int num = 0;                    // stores the number of regions

    struct Pos { int i; int j; };   // position on the grid
    
    std::stack<Pos> posStack;       // stack used for search
    Grid isSeen{};                  // used to keep track of seen positions

    // lambda to generate vector of neighboring positions
    auto genNeighbors = [](Pos p) {
        std::vector<Pos> neighbors;
        if (p.i > 0)        neighbors.push_back(Pos{p.i-1,  p.j});
        if (p.j > 0)        neighbors.push_back(Pos{p.i,    p.j-1});
        if (p.i < 127)      neighbors.push_back(Pos{p.i+1,  p.j});
        if (p.j < 127)      neighbors.push_back(Pos{p.i,    p.j+1});
        return neighbors;
    };

    // for each cell in the grid:
    for (int i = 0; i < 128; ++i) {
        for (int j = 0; j < 128; ++j) {

            // if we haven't visited it before, and it's set -> it's a new 
            // region. search through the region to set all squares in the 
            // region to seen
            if (!isSeen[i][j] && grid[i][j]) {

                posStack.push(Pos{i, j});   // stack of positions to visit
                Pos curr;                   // stores current pos in search

                // while there are postions to visit in the region -> visit one 
                // at a time and add all it's neighbors to the stack
                while (!posStack.empty()) {

                    // pop pos of the stack and set it to seen
                    curr = posStack.top();
                    posStack.pop();
                    isSeen[curr.i][curr.j] = true;

                    // for each neighbor (that is also set, and isn't seen 
                    // yet) -> add to stack
                    for (Pos neighbor : genNeighbors(curr)) {
                        if (!isSeen[neighbor.i][neighbor.j] && grid[neighbor.i][neighbor.j]) {
                            posStack.push(neighbor);
                        }
                    }
                }

                // we've seen a new region. increment region count
                ++num;
            }
        }
    }

    return num;
}

// count number of squares set to true in the grid (for part 1)
int numSet(const Grid& grid) {
    int count = 0;
    for (const auto& row : grid)
        for (const auto& square : row)
            if (square)
                ++count;

    return count;
}

// generate grid from string input
Grid generate(std::string input) {
    
    Grid grid{};

    // for each i=0..127 generate a string [input]-i and binHash it. grid[i] is 
    // the binHash of that string
    for (int i = 0; i < 128; ++i) {
        auto rowInput = input;
        rowInput.append("-");
        rowInput.append(std::to_string(i));

        grid[i] = hashToBin(knotHash(rowInput));
    }

    return grid;
}

int main() {

    auto grid = generate("nbysizxe");

    std::cout << numSet(grid) << std::endl;
    std::cout << numRegions(grid) << std::endl;

    return 0;
} 
