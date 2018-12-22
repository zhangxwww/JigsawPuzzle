#include "JigsawPuzzle.h"
#include "Archive.h"
#include "Util.h"

#include <iostream>
#include <random>
#include <ctime>
#include <deque>
#include <set>
#include <cmath>

JigsawPuzzle::JigsawPuzzle(
    const int row, const int col)

    : row(row), col(col), matrix(nullptr),
    originMatrix(nullptr),
    curBlankRow(row - 1), curBlankCol(col - 1) {

    matrix = new int[row * col];
    originMatrix = new int[row * col];
    for (int i = 0; i < row * col - 1; i++) {
        matrix[i] = i;
        originMatrix[i] = i;
    }
    matrix[row * col - 1] = -1;
    originMatrix[row * col - 1] = -1;

}

JigsawPuzzle::JigsawPuzzle(const Archive & archive)
    : row(archive.row), col(archive.col), matrix(nullptr),
    originMatrix(nullptr), curBlankRow(0), curBlankCol(0) {

    matrix = new int[row * col];
    originMatrix = new int[row * col];

    for (int i = 0; i < row * col; i++) {
        matrix[i] = archive.matrix[i];
        originMatrix[i] = archive.matrix[i];
        if (matrix[i] == -1) {
            curBlankRow = i / col;
            curBlankCol = i % col;
        }
    }
}

JigsawPuzzle::~JigsawPuzzle() {
    if (matrix != nullptr) {
        delete[] matrix;
    }
    if (originMatrix != nullptr) {
        delete[] originMatrix;
    }
}

void JigsawPuzzle::shuffle() {
    std::default_random_engine e;
    e.seed(std::time(0));
    std::uniform_int_distribution<unsigned> u(0, 1000);
    for (int i = 0; i < row * col - 1; i++) {
        matrix[i] = i;
    }
    matrix[row * col - 1] = -1;
    // 对每一个数，依次交换其与其之后的随机位置上的数
    for (int i = 0; i < row * col - 1; i++) {
        unsigned r = u(e) % (row*col - 1 - i) + i;
        swap<int>(matrix[i], matrix[r]);
    }
    for (int i = 0; i < row * col; i++) {
        originMatrix[i] = matrix[i];
    }
    curBlankRow = row - 1;
    curBlankCol = col - 1;
}

bool JigsawPuzzle::move(const char c) {
    switch (c) {
    case 'W':
        if (curBlankRow > 0) {
            curBlankRow--;
            swap<int>(matrix[curBlankRow * col + curBlankCol],
                matrix[(curBlankRow + 1) * col + curBlankCol]);
            return true;
        }
        break;
    case 'A':
        if (curBlankCol > 0) {
            curBlankCol--;
            swap<int>(matrix[curBlankRow * col + curBlankCol],
                matrix[curBlankRow * col + curBlankCol + 1]);
            return true;
        }
        break;
    case 'S':
        if (curBlankRow < row - 1) {
            curBlankRow++;
            swap<int>(matrix[curBlankRow * col + curBlankCol],
                matrix[(curBlankRow - 1) * col + curBlankCol]);
            return true;
        }
        break;
    case 'D':
        if (curBlankCol < col - 1) {
            curBlankCol++;
            swap<int>(matrix[curBlankRow * col + curBlankCol],
                matrix[curBlankRow * col + curBlankCol - 1]);
            return true;
        }
        break;
    default:
        break;
    }
    return false;
}

bool JigsawPuzzle::moveBack(const char c) {
    switch (c) {
    case 'W':
        return move('S');
        break;
    case 'A':
        return move('D');
        break;
    case 'S':
        return move('W');
        break;
    case 'D':
        return move('A');
        break;
    default:
        break;
    }
    return false;
}

bool JigsawPuzzle::isFinished() const {
    for (int i = 0; i < row * col - 1; i++) {
        if (matrix[i] != i) {
            return false;
        }
    }
    return true;
}

void JigsawPuzzle::restart() {
    for (int i = 0; i < row * col; i++) {
        matrix[i] = originMatrix[i];
    }
    curBlankCol = col - 1;
    curBlankRow = row - 1;
}

bool JigsawPuzzle::feasibilityAnalysis() const {
    int inversionPair = 0;
    // 计算逆序对数，-1除外，有解<=>逆序对数为偶数
    for (int i = 0; i < row * col - 1; i++) {
        for (int j = i + 1; j < row * col; j++) {
            if (matrix[i] == -1
                || matrix[j] == -1) {
                continue;
            }
            if (matrix[i] > matrix[j]) {
                inversionPair++;
            }
        }
    }
    if (inversionPair % 2 == 0) {
        return true;
    }
    else {
        return false;
    }
}

void JigsawPuzzle::autoFinish() {
    int * originState = new int[row * col];
    for (int i = 0; i < row * col; i++) {
        originState[i] = matrix[i];
    }
    std::deque<char> waiting;
    std::deque<char> path;
    std::set<long long> exploitedStates;
    bool moved = true;
    exploitedStates.insert(hash());
    char c;
    do {
        if (isFinished()) {
            break;
        }
        if (moved) {
            int score[4] = { -1,-1,-1,-1 };
            bool canmove = false;
            if (move('W')) {
                if (exploitedStates.find(hash()) == exploitedStates.end()) {
                    score[0] = distance();
                    canmove = true;
                }
                move('S');
            }
            if (move('A')) {
                if (exploitedStates.find(hash()) == exploitedStates.end()) {
                    score[1] = distance();
                    canmove = true;
                }
                move('D');
            }
            if (move('S')) {
                if (exploitedStates.find(hash()) == exploitedStates.end()) {
                    score[2] = distance();
                    canmove = true;
                }
                move('W');
            }
            if (move('D')) {
                if (exploitedStates.find(hash()) == exploitedStates.end()) {
                    score[3] = distance();
                    canmove = true;
                }
                move('A');
            }
            for (int i = 0; i < 4 && canmove; i++) {
                int max = -1;
                int index = 0;
                for (int j = 0; j < 4; j++) {
                    if (score[j] > max) {
                        max = score[j];
                        index = j;
                    }
                }
                if (index == 0 && score[index] != -1) {
                    waiting.push_back('W');
                }
                else if (index == 1 && score[index] != -1) {
                    waiting.push_back('A');
                }
                else if (index == 2 && score[index] != -1) {
                    waiting.push_back('S');
                }
                else if(score[index] != -1){
                    waiting.push_back('D');
                }
                score[index] = -1;
            }
            if (!canmove) {
                c = path.back();
                path.pop_back();
                moveBack(c);
            }
        }
        if (waiting.empty()) {
            break;
        }
        c = waiting.back();
        waiting.pop_back();
        move(c);
        if (exploitedStates.find(hash()) != exploitedStates.end()) {
            moveBack(c);
            moved = false;
        }
        else {
            moved = true; 
            path.push_back(c);
            exploitedStates.insert(hash());
        }
    } while (!waiting.empty());
    for (int i = 0; i < row * col; i++) {
        matrix[i] = originState[i];
    }
    return;
}

int * JigsawPuzzle::getMatrix() const {
    return matrix;
}

const int JigsawPuzzle::getRow() const {
    return row;
}

const int JigsawPuzzle::getCol() const {
    return col;
}

long long JigsawPuzzle::hash() const {
    long long base = row * col;
    long long result = 0;
    for (int i = 0; i < row * col; i++) {
        result = matrix[i] + 1 + result * base;
    }
    return result;
}

int JigsawPuzzle::distance() const {
    int d = 0;
    for (int i = 0; i < row * col; i++) {
        int r = i / row;
        int c = i % row;
        if (matrix[i] == -1) {
            d += abs(row - 1 - r) + abs(col - 1 - c);
        }
        else {
            d += abs(matrix[i] / row - r) + abs(matrix[i] % row - c);
        }
    }
    return d;
}


