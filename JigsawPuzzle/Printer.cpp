#include "Printer.h"
#include "Util.h"

#include <iostream>
#include <cstdlib>

Printer::Printer(const int row, const int col)
    : row(row), col(col) {
}

Printer::~Printer() {
}

void Printer::printMatrix(int * matrix) {
    setCurRow(0);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            std::cout << matrix[i * col + j] << '\t';
        }
        std::cout << "\t\t\t";
        std::cout << std::endl;
    }
}

void Printer::printText(const std::string & text) {
    clearText();
    std::cout << text << std::endl;
}

void Printer::printPath(std::deque<char> path) {
    clearText();
    while (!path.empty()) {
        for (int i = 0; i < 60; i++) {
            if (path.empty()) {
                break;
            }
            char c = path.front();
            path.pop_front();
            std::cout << c;
        }
        std::cout << std::endl;
    }
}

void Printer::clearText() {
    int curRow = getCurRow();
    setCurRow(row);
    for (int i = row; i < curRow; i++) {
        std::cout << "                                                            "
            << std::endl;
    }  
    setCurRow(row);
}
