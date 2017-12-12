#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

struct Node {
    std::vector<int> neighborList;      // list of indexes of neighboring nodes
    int group;                          // group it belongs to (0 if none)
};

// give each node connected to 'curr' the id 'id'. Also return number of nodes
// in that group
int groupify(std::vector<Node> &nodes, int curr, int id) {

    // if already has group -> we don't care about this node -> early return
    if (nodes[curr].group != 0) {
        return 0; 
    }

    nodes[curr].group = id;     // set group id

    // sum up number of neighbors + 1 (itself)
    int sum = 1;
    for (auto i : nodes[curr].neighborList) {

        // use same function recursively with neighbor index
        sum += groupify(nodes, i, id);
    }

    return sum;
}

// read input and return vector of nodes.
// NOTE: function relies on nodes having sequential ids in the file, as well 
//  as the ids being the row number of the node in the file
// (Could have avoided this with use of map, but chose vector because input was
//  ordered nicely)
std::vector<Node> readInput(std::string inputFile) {

    std::vector<Node> nodes;
    std::ifstream ifs(inputFile);

    // temp variables used for reading:
    int node, neighbor;
    char dummyChar;
    std::string dummyStr;

    // read all nodes in the file into 'nodes'
    std::string line;
    while (std::getline(ifs, line)) {

        std::istringstream iss(line);

        iss >> node;                    // read node

        nodes.push_back(Node{{}, 0});   // add node to vector (no group)

        iss >> dummyStr;                // skip arrows

        // add neighbors to neighborslist
        while (iss >> neighbor) {
            nodes.back().neighborList.push_back(neighbor);
            iss >> dummyChar;                               // read comma
        }

    }

    return nodes;
}

int main() {

    auto nodes = readInput("input/input_day12.txt");

    // groupify all nodes, and count up new groups found
    int numGroups = 0, groupID;
    for (int i = 0; i < nodes.size(); ++i) {    // try and groupify all elements
        groupID = i+1;                          // generate unique id for group
        groupify(nodes, i, groupID);        
        if (nodes[i].group == groupID) { // if a new group was found this node
            ++numGroups;                 //  will have the id we groupified with
        }
    }

    std::cout << "Part 1: " << nodes[0].group << std::endl;
    std::cout << "Part 2: " << numGroups << std::endl;

    return 0;
} 
