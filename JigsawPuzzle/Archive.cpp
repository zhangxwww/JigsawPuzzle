#include "Archive.h"

Archive::Archive()
    :name(""), row(0), col(0), 
    matrix(nullptr) {
}

Archive::Archive(const std::string & name, 
    const int row, const int col, int * matrix)
    : name(name), row(row), col(col), matrix(nullptr) {

    this->matrix = new int[row * col];
    for (int i = 0; i < row * col; i++) {
        this->matrix[i] = matrix[i];
    }
}

Archive::~Archive() {
    if (matrix != nullptr) {
        delete matrix;
    }
}
