#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <string>
#include <sstream>



std::string part1(std::string inputFile) {

    std::vector<std::string> nodes;         // nodes in the tower
    std::set<std::string> neighbors;     // nodes that are neighbors

    // First, read through file and populate containers
    std::ifstream ifs(inputFile);

    std::string line;
    while (getline(ifs, line)) {

        std::string node;
        std::istringstream iss(line);
        
        iss >> node; // read name of node
        //std::cout << node << " ----  ";
        nodes.push_back(node);

        // if it has neighbors, read those
        iss >> node >> node;                // skip beyond arrow
        while (iss >> node) {
            if (node[node.length()-1] == ',') {
                node = node.substr(0, node.length()-1);
            }
            //std::cout << node << " ";
            neighbors.insert(node);
        }
        //std::cout << '\n';
    }

    // find node in nodes that is not in neighbors: (isn't a neighbor)
    std::string bottomNode;
    for (std::string node : nodes) {
        if (neighbors.find(node) == neighbors.end()) {
            bottomNode = node;
            break;
        }
    }

    return bottomNode;
}

struct BasicNode {
    std::string name;
    std::vector<std::string> neighbors;
};

std::vector<BasicNode> readNodes(std::string inputFile) {
    
    std::ifstream ifs(inputFile);
    std::vector<BasicNode> nodes;

    // for each node on file
    std::string line;
    while (getline(ifs, line)) {
        BasicNode currentNode;

        std::string node;
        std::istringstream iss(line);
        
        iss >> node; // read name of node
        currentNode.name = node; 

        // if it has neighbors, read those
        iss >> node >> node;                // skip beyond arrow
        while (iss >> node) {
            if (node[node.length()-1] == ',') {
                node = node.substr(0, node.length()-1);
            }
            currentNode.neighbors.push_back(node);
        }
        nodes.push_back(currentNode);
    }

    for (BasicNode n : nodes) {
        std::cout << n.name << "-----";
        for (auto nei : n.neighbors) {
            std::cout << nei << ", ";
        }
        std::cout << std::endl;
    }

    return nodes;
}

struct Node {
    std::string name;
    std::vector<Node*> neighbors;
};

std::vector<Node*> convert(std::vector<BasicNode> basicNodes) {

    std::vector<Node*> nodes;

    // populate nodes
    for (BasicNode bn : basicNodes) {
        nodes.push_back(new Node{name: bn.name});
    }

    // assign neighbors
    for (BasicNode bn : basicNodes) {

        // find node with basicNode name
        Node* node;
        for (Node* n : nodes) {
            if (n->name == bn.name) {
                node = n;
                break;
            }
        }

        if (!node) {
            std::cout << "ERROR: couldn't find BasicNode in nodes\n";
        }

        for (std::string neighborName : bn.neighbors) {

            // look for node with neighbor name in nodes
            Node* neighbor;
            for (Node* node : nodes) {
                if (node->name == neighborName) {
                    neighbor = node;
                    break;
                }
            }

            if (!neighbor) {
                std::cout << "ERROR: couldn't find neighbor in nodes\n";
            }

            node->neighbors.push_back(neighbor);
        }
    }

    return nodes;
}

int findImbalance(Node* root) {


    
    return 0;
}

int part2(std::string inputFile) {

    auto bnodes = readNodes(inputFile);

    auto nodes = convert(bnodes);

    // find root
    Node* root;
    std::string rootName = part1(inputFile);
    for (Node* n : nodes) {
        if (n->name == rootName) {
            root = n;
            break;
        }
    }

    if (!root) {
        std::cout << "ERROR: couldn't find root\n";
    }

    // find imbalance
    findImbalance(root);

    for (Node* np : nodes) {    // remember to delete!!
        delete np;
    }

    return 0;
}

int main() {

    std::cout << "Part 1: " << part1("input/input_day7.txt") << std::endl;
    std::cout << "Part 2: " << part2("input/input_day7_test.txt") << std::endl;

    return 0;
} 
