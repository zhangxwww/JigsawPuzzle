#include "BMPStorer.h"

#include <fstream>

BMPStorer::BMPStorer(
    std::ifstream & bmpFile) {

    bmpFile.seekg(18, std::ios::beg);
    bmpFile.read((char *)& originWidth, sizeof(int));
    bmpFile.read((char *)& originHeight, sizeof(int));
    originB = new unsigned int[originWidth * originHeight];
    originG = new unsigned int[originWidth * originHeight];
    originR = new unsigned int[originWidth * originHeight];

    bmpFile.seekg(54, std::ios::beg);
    unsigned char c;
    for (int i = 0; i < originWidth * originHeight; i++) {
        bmpFile.read((char *)& c, sizeof(unsigned char));
        originB[i] = c;
        bmpFile.read((char *)& c, sizeof(unsigned char));
        originG[i] = c;
        bmpFile.read((char *)& c, sizeof(unsigned char));
        originR[i] = c;
    }

    bmpFile.seekg(0, std::ios::beg);
    bmpFile.read(header, 54 * sizeof(char));
}

BMPStorer::~BMPStorer() {
    delete[] originR;
    delete[] originG;
    delete[] originB;
}

void BMPStorer::setSize(
    const int row, const int col) {

    this->row = row;
    this->col = col;
}

void BMPStorer::refactor(int * matrix) {
    unsigned int * nB = new unsigned int[originWidth * originHeight];
    unsigned int * nG = new unsigned int[originWidth * originHeight];
    unsigned int * nR = new unsigned int[originWidth * originHeight];
    for (int i = 0; i < originWidth * originHeight; i++) {
        nB[i] = 0;
        nG[i] = 0;
        nR[i] = 0;
    }
    // 块的宽、高
    int deltaWidth = originWidth / col;
    int deltaHeight = originHeight / row;
    // 新的图像的宽、高
    int newWidth = deltaWidth * col;
    int newHeight = deltaHeight * row;
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            int order = matrix[r * col + c];
            if (order == -1) {
                continue;
            }
            // 初始位置
            int preCol = order % col;
            int preRow = order / col;
            // 正在绘制的块的左下坐标
            int newLeftDownPixY = (row - r - 1) * deltaHeight;
            int newLeftDownPixX = c * deltaWidth;
            // 正在绘制的块在原图中的左下坐标
            int preLeftDownPixY = (row - preRow - 1) * deltaHeight;
            int preLeftDownPixX = preCol * deltaWidth;
            for (int y = 0; y < deltaHeight; y++) {
                for (int x = 0; x < deltaWidth; x++) {
                    nB[x + newLeftDownPixX + (y + newLeftDownPixY) * newWidth]
                        = originB[x + preLeftDownPixX + (y + preLeftDownPixY) * newWidth];
                    nG[x + newLeftDownPixX + (y + newLeftDownPixY) * newWidth]
                        = originG[x + preLeftDownPixX + (y + preLeftDownPixY) * newWidth];
                    nR[x + newLeftDownPixX + (y + newLeftDownPixY) * newWidth]
                        = originR[x + preLeftDownPixX + (y + preLeftDownPixY) * newWidth];
                }
            }
        }
    }
    drawingWidth = newWidth;
    drawingHeight = newHeight;
    delete[] drawingB;
    delete[] drawingG;
    delete[] drawingR;
    drawingB = nB;
    drawingG = nG;
    drawingR = nR;
}

void BMPStorer::drawBounds() {
    int deltaWidth = drawingWidth / col;
    int deltaHeight = drawingHeight / row;
    // 绘制所有竖线
    for (int c = 1; c < col; c++) {
        for (int y = 0; y < drawingHeight; y++) {
            drawingB[y * originWidth + c * deltaWidth] = 0;
            drawingG[y * originWidth + c * deltaWidth] = 0;
            drawingR[y * originWidth + c * deltaWidth] = 0;
        }
    }
    // 绘制所有横线
    for (int r = 1; r < row; r++) {
        for (int x = 0; x < drawingWidth; x++) {
            drawingB[r * deltaHeight * originWidth + x] = 0;
            drawingG[r * deltaHeight * originWidth + x] = 0;
            drawingR[r * deltaHeight * originWidth + x] = 0;
        }
    }
}

void BMPStorer::save(std::ofstream & bmpFile) {
    bmpFile.write(header, 54 * sizeof(char));
    bmpFile.seekp(18, std::ios::beg);
    bmpFile.write((char *)& drawingWidth, sizeof(int));
    bmpFile.write((char *)& drawingHeight, sizeof(int));
    bmpFile.seekp(54, std::ios::beg);
    unsigned char c;
    for (int i = 0; i < drawingWidth * drawingHeight; i++) {
        c = drawingB[i];
        bmpFile.write((char *)(&c), sizeof(unsigned char));
        c = drawingG[i];
        bmpFile.write((char *)(&c), sizeof(unsigned char));
        c = drawingR[i];
        bmpFile.write((char *)(&c), sizeof(unsigned char));
    }
}
