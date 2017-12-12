#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <fstream>

int count(std::map<int, std::vector<int>> neighborList, int curr) {

    static std::set<int> seen;

    if (seen.find(curr) != seen.end()) {
        return 0;
    }

    seen.insert(curr);

    int sum = 1;

    for (auto i : neighborList[curr]) {
        sum += count(neighborList, i);
    }

    return sum;
}

int main() {

    std::map<int, std::vector<int>> neighborList;

    std::ifstream ifs("input/input_day12.txt");

    std::string line;
    while (std::getline(ifs, line)) {

        std::istringstream iss(line);

        int node;
        iss >> node; // read node

        std::cout << node << " -- ";

        neighborList[node];

        std::string dummyStr;
        iss >> dummyStr; // skip arrows

        int neighbor;
        char dummyChar;
        while (iss >> neighbor) {

            std::cout << neighbor << " ";

            neighborList[node].push_back(neighbor);
            
            iss >> dummyChar;
        }

        std::cout << std::endl;
    }

    std::cout << count(neighborList, 0) << std::endl;

    return 0;
} 
