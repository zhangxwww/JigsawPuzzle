#include "JigsawPuzzle.h"
#include "Archive.h"
#include "Util.h"

#include <iostream>
#include <random>
#include <ctime>

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
    // 用originMatrix保存打乱后的状态
    for (int i = 0; i < row * col; i++) {
        originMatrix[i] = matrix[i];
    }
    curBlankRow = row - 1;
    curBlankCol = col - 1;
}

void JigsawPuzzle::move(const char c) {
    switch (c) {
    case 'W':
        if (curBlankRow > 0) {
            curBlankRow--;
            swap<int>(matrix[curBlankRow * col + curBlankCol],
                matrix[(curBlankRow + 1) * col + curBlankCol]);
        }
        break;
    case 'A':
        if (curBlankCol > 0) {
            curBlankCol--;
            swap<int>(matrix[curBlankRow * col + curBlankCol],
                matrix[curBlankRow * col + curBlankCol + 1]);
        }
        break;
    case 'S':
        if (curBlankRow < row - 1) {
            curBlankRow++;
            swap<int>(matrix[curBlankRow * col + curBlankCol],
                matrix[(curBlankRow - 1) * col + curBlankCol]);
        }
        break;
    case 'D':
        if (curBlankCol < col - 1) {
            curBlankCol++;
            swap<int>(matrix[curBlankRow * col + curBlankCol],
                matrix[curBlankRow * col + curBlankCol - 1]);
        }
        break;
    default:
        break;
    }
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

int * JigsawPuzzle::getMatrix() const {
    return matrix;
}

const int JigsawPuzzle::getRow() const {
    return row;
}

const int JigsawPuzzle::getCol() const {
    return col;
}
