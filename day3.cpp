#include <iostream>
#include <vector>
#include <array>

// regn ut steps for å komme seg fra num'te element i snegle til midten 
// ved manhattan distance
int steps(int num) {

    if (num == 1) {     // ..er allerede i midten
        return 0;
    }
    
    // finn ut hvilken ring det er i:
    int ring;

    int total = 1, lastInRing, ringSize;
    for (int i = 1; i < num; ++i) {
        ringSize = ((i-1)*2 + 1)*4 + 4;
        lastInRing = ringSize + total;
        if (num <= lastInRing) {
            ring = i;
            break;
        }
        total += ringSize;
    }


    // finn ut hvilken side det er i, og regn diff til midten
    int middle = lastInRing - ring;
    int smallestDiff = std::abs(num - middle);
    for (int i = 0; i < 3; ++i) {
        middle -= ring*2;
        int diff = std::abs(num - middle);
        if (diff < smallestDiff) {
            smallestDiff = diff;
        }
    }
    
    // manhattan = ring + distansen til midten
    return smallestDiff + ring;
}

// (ikke spesielt stolt av denne)
// finn svaret ved å regne på samme måte som en ville gjort på papir..
// tegn inn i 2-dimensjonelt array rundt og rundt til funnet svar
int part2(int input) {

    std::array<std::array<int, 21>, 21> board = {};

    int posx = 10, posy = 10;

    board[posx][posy] = 1;

    int dir = 0, step = 0, max = 1;
    while (true) {
        
        if (dir == 0) {
            posx += 1;
        } else if (dir == 1) {
            posy -= 1;
        } else if (dir == 2) {
            posx -= 1;
        } else if (dir == 3) {
            posy += 1;
        }

        ++step;

        if (step == max) {
            dir = (dir + 1) % 4;
            step = 0;
            if (dir % 2 == 0) {
                max++;
            }
        }

        int neighbors = 0;
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                neighbors += board[posx+j-1][posy+k-1];
            }
        }
        board[posx][posy] = neighbors;

        if (neighbors > input) {
            return neighbors;
        }
    }


    return 0;
}

int main() {

    int input = 312051;

    std::cout << "Part 1: " << steps(input) << std::endl;
    std::cout << "Part 2: " << part2(input) << std::endl;

    return 0;
}
