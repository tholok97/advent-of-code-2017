#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

// typedef cause tedious to type
typedef std::vector<std::vector<int>> Rows;

// returns rows from inputfile
Rows readInput() {

    Rows rows;

    std::ifstream ifs("input.txt");

    std::string line;
    while (std::getline(ifs, line)) {

        std::vector<int> row;
        std::istringstream iss(line);

        int col;
        while (iss >> col) {
            row.push_back(col);
        }

        rows.push_back(row);
    }

    return rows;
}

// calculate checkusum of rows
int checksum(Rows rows) {

    int sum = 0;

    // for each row
    for (auto row : rows) {

        // find smallest
        int min = *std::min_element(row.begin(), row.end());
        
        // find biggest
        int max = *std::max_element(row.begin(), row.end());
        
        // calc diff
        int diff = max - min;

        // add diff to sum
        sum += diff;
    }

    return sum;
}

// checksum is the sum of each row's evenly divisible pair
int checksum2(Rows rows) {

    int sum = 0;

    // for each row
    for (auto row : rows) {
        
        // combine all until found two evenly divisible
        int size = row.size();
        bool found = false;
        for (int i = 0 ; i < size-1; ++i) {
            found = false;
            for (int j = i+1; j < size; ++j) {
                if (row[i] % row[j] == 0) {
                    sum += row[i] / row[j]; 
                    found = true;

                } else if (row[j] % row[i] == 0) {
                    sum += row[j] / row[i]; 
                    found = true;
                }
            }

            if (found) {
                break;
            }
        }
    }

    return sum;
}

int main() {

    Rows rows = readInput();

    std::cout << "Part 1: " << checksum(rows) << std::endl;
    std::cout << "Part 2: " << checksum2(rows) << std::endl;

    return 0;
} 
