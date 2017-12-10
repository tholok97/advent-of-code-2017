#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

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

// part 1: do knot hash once, return [0] * [1]
int part1(std::string input, int listSize) {
    auto lengths = strtoivec(input);
    auto list = knotHashRounds(lengths, listSize, 1);
    return list[0] * list[1];
}

int main() {

    auto input = "227,169,3,166,246,201,0,47,1,255,2,254,96,3,97,144";

    std::cout << "Part 1: " << part1(input, 256) << std::endl;
    std::cout << "Part 2: " << knotHash(input) << std::endl;

    //std::cout << "KnotHash of \"Thomas er kul\" -> " << 
    //        knotHash("Thomas er kul") << std::endl;

    return 0;
} 
