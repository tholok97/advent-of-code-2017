/*
 * WARNING! For your own safety, don't try and follow my solution to part 2 
    until I've cleaned it up. Currently it's a soup of sparsely commented and
    barely working code. You have been warned.... It works though. Gave me the 
    answer and everything :D
 * Part 1 works and is reasonably commented.
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <set>
#include <string>
#include <sstream>

std::string part1(std::string inputFile) {

    std::vector<std::string> nodes;         // nodes in the tower
    std::set<std::string> neighbors;        // nodes that are neighbors

    // First, read through file and populate containers
    std::ifstream ifs(inputFile);

    std::string line;
    while (getline(ifs, line)) {

        std::string node;
        std::istringstream iss(line);
        
        iss >> node; // read name of node
        nodes.push_back(node);

        // if it has neighbors, read those
        iss >> node >> node;                // skip beyond arrow
        while (iss >> node) {
            if (node[node.length()-1] == ',') {
                node = node.substr(0, node.length()-1);
            }
            neighbors.insert(node);
        }
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
    int weight;
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

        // read weight
        std::string weightWord;
        iss >> weightWord;
        currentNode.weight = std::stoi(weightWord.substr(1, weightWord.length()-2));

        // if it has neighbors, read those
        iss >> node;                // skip beyond arrow
        while (iss >> node) {
            if (node[node.length()-1] == ',') {
                node = node.substr(0, node.length()-1);
            }
            currentNode.neighbors.push_back(node);
        }
        nodes.push_back(currentNode);
    }


    return nodes;
}

struct Node {
    std::string name;
    int weight;
    std::vector<Node*> neighbors;
};

std::vector<Node*> convert(std::vector<BasicNode> basicNodes) {

    std::vector<Node*> nodes;

    // populate nodes
    for (BasicNode bn : basicNodes) {
        nodes.push_back(new Node{name: bn.name, weight: bn.weight});
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

void debugPrint(Node* node) {
    std::cout << node->name << " (" << node->weight << ") ";
    if (!node->neighbors.empty()) {
        std::cout << " has neighboor(s): ";
        for (Node* n : node->neighbors) {
            debugPrint(n);
        }
    }

    std::cout << "|";
}

// gives sum of nodes in (sub)tree pointed to by node
int treeSum(Node* node) {
    if (node->neighbors.empty()) {
        return node->weight;
    }

    int sum = node->weight;
    for (Node* neighbor : node->neighbors) {
        sum += treeSum(neighbor); 
    }

    return sum;
}

bool childrenBalanced(Node* node) {
    if (node->neighbors.size() < 2) {   // less than 2 children: always balanced
        return true;
    } 
    
    // >= 2 children: check for balance
    bool balanced = true;

    // for each sequential pair: check for equality. If not equal: not balanced
    for (int i = 1; i < node->neighbors.size(); ++i) {
        if (treeSum(node->neighbors[i]) != treeSum(node->neighbors[i-1])) {
            balanced = false;
        }
    }

    return balanced;
}

int findImbalance(Node* root) {

    int correctedVal;   // value invalid node gets after balancing

    Node* curr = root;
    int parentDiff = 0;
    int correctWeight = -923;

    // keep looking until found node where children are balanced
    while (!childrenBalanced(curr)) {

        // find unbalanced subtree
        Node* unbalanced;
        if (curr->neighbors.size() > 2) {
            
            // just find the odd one out
            std::vector<int> sums;       // i -> index in neighbors
            for (int i = 0; i < curr->neighbors.size(); ++i) {
                sums.push_back(treeSum(curr->neighbors[i]));
            }

            int indexOfUnbalanced = -1;
            for (int i = 0; i < sums.size(); ++i) {
                if (std::count(sums.begin(), sums.end(), sums[i]) == 1) {
                    indexOfUnbalanced = i;
                    break;
                }
            }

            if (indexOfUnbalanced == -1) {
                std::cout << "LKSDJ wrong input";
                std::abort();
            }

            // choose odd one out as next curr
            unbalanced = curr->neighbors[indexOfUnbalanced];

            if (indexOfUnbalanced > 0) {
                correctWeight = sums[indexOfUnbalanced-1];
            } else {
                correctWeight = sums[1];
            }
        } else {

            // if this happens my solution doens't work...
            if (parentDiff == 0) {
                std::cout << "CRISIS: first neighbors encountered are twins";
                std::abort();
            }

            // if parentDiff > 0: choose bigger, if not choose smaller
            Node* n0 = curr->neighbors[0];
            Node* n1 = curr->neighbors[1];
            int sum0 = treeSum(n0);
            int sum1 = treeSum(n1);
            if (sum0 > sum1 && parentDiff || sum0 < sum1 && !parentDiff) {
                unbalanced = n0;
                correctWeight = sum1;
            } else {
                unbalanced = n1;
                correctWeight = sum0;
            }
        }
        
        // set curr to this one and repeat
        curr = unbalanced;
    }

    // children are balanced, but curr isn't. Balance curr!

    // my weight should be correctWeight - the sum of my children
    int childrenSum = 0;
    for (Node* child : curr->neighbors) {
        childrenSum += treeSum(child);
    }

    return correctWeight - childrenSum;
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

    // find imabalance
    int ret = findImbalance(root);
    
    for (Node* np : nodes) {    // remember to delete!!
        delete np;
    }

    return ret;
}

int main() {

    std::cout << "Part 1: " << part1("input/input_day7.txt") << std::endl;
    std::cout << "Part 2: " << part2("input/input_day7.txt") << std::endl;

    return 0;
} 
