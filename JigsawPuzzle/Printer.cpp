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

void Printer::clearText() {
    setCurRow(row);
    for (int i = 0; i < 15; i++) {
        std::cout << "                                                        "
            << std::endl;
    }  
    setCurRow(row);
}
