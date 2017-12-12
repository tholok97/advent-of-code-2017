#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <fstream>

using Node = std::pair<std::vector<int>, int>;

int count(std::map<int, Node> &nodes, int curr, int id) {

    if (nodes[curr].second) {
        return 0; 
    }

    nodes[curr].second = id;

    int sum = 1;

    for (auto i : nodes[curr].first) {
        sum += count(nodes, i, id);
    }

    return sum;
}

int main() {

    std::map<int, Node> nodes;

    std::ifstream ifs("input/input_day12.txt");

    std::string line;
    while (std::getline(ifs, line)) {

        std::istringstream iss(line);

        int node;
        iss >> node; // read node


        nodes[node].second = 0;

        std::string dummyStr;
        iss >> dummyStr; // skip arrows

        int neighbor;
        char dummyChar;
        while (iss >> neighbor) {


            nodes[node].first.push_back(neighbor);
            
            iss >> dummyChar;
        }

    }

    std::set<int> seen;

    for (int i = 0; i < 2000; ++i) {
        count(nodes, i, i+1);

        seen.insert(nodes[i].second);
    }

    std::cout << seen.size() << std::endl;

    return 0;
} 
