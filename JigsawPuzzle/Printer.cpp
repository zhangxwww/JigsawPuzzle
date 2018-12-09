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
    clearScreen();
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            std::cout << matrix[i * col + j] << '\t';
        }
        std::cout << std::endl;
    }
}
