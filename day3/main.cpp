 /* 
    x x x x x
    x 5 4 3 x
    x 6 1 2 x
    x 7 8 9 x
    x x x x x



    1   | 2 3 4 5 6 7 8 9   | 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25   | ...       | ...
    x1  | x8                | (3*4 + 4)=x16                                     | x24       | 

    9 2 3     3 4 5      5 6 7     7 8 9
    24 25 10 11 12   12 13 14 15 16     16 17 18 19 20   20 21 22 23 24

    0: 1
    1: ((1 + (1-1)*2)*4 + 4) = 8
    2: ((2 + (2-1)*2)*4 + 4) = 16
    3: ((3 + (3-1)*2)*4 + 4) = 24
    4: (7*4 + 4) = 32

    1 -- 1 -- (1-1)*2 + 1
    2 -- 3 -- (2-1)*2 + 1
    3 -- 5 -- (3-1)*2 + 1
    4 -- 7 -- (4-1)*2 + 1
    5 -- 9



    x = 11
    if (x == 1) {
        // x er i ring 1
    }

    for (int i = 1; i < x; i+=2) {
        if (x < (i*4 + 4)) {
            // x er i ring i
        }
    }

    // finn ut hvilken ring det er i:
    //      (for-løkka over)
    // finn ut hvilken side det er i
    // finn distansen til midten av siden
    //
    // manhattan = ring + distansen til midten

 */

#include <iostream>
#include <vector>
#include <array>

int whichRing(int num) {
}

int steps(int num) {

    if (num == 1) {
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


    // finn ut hvilken side det er i
        // finn de fire sidene?
    int middle = lastInRing - ring;
    int smallestDiff = std::abs(num - middle);
    for (int i = 0; i < 3; ++i) {
        middle -= ring*2;
        int diff = std::abs(num - middle);
        if (diff < smallestDiff) {
            smallestDiff = diff;
        }
    }

    // finn distansen til midten av siden
    
    // manhattan = ring + distansen til midten
    return smallestDiff + ring;
}

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
