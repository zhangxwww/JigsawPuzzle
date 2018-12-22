#include "BMPStorer.h"

#include <fstream>

BMPStorer::BMPStorer(
    std::ifstream & bmpFile) {

    bmpFile.seekg(18, std::ios::beg);
    bmpFile.read((char *)& width, sizeof(int));
    bmpFile.read((char *)& height, sizeof(int));
    B = new unsigned int[width * height];
    G = new unsigned int[width * height];
    R = new unsigned int[width * height];

    bmpFile.seekg(54, std::ios::beg);
    unsigned char c;
    for (int i = 0; i < width * height; i++) {
        bmpFile.read((char *)& c, sizeof(unsigned char));
        B[i] = c;
        bmpFile.read((char *)& c, sizeof(unsigned char));
        G[i] = c;
        bmpFile.read((char *)& c, sizeof(unsigned char));
        R[i] = c;
    }

    bmpFile.seekg(0, std::ios::beg);
    bmpFile.read(header, 54 * sizeof(char));
}

BMPStorer::~BMPStorer() {
    delete[] R;
    delete[] G;
    delete[] B;
}

void BMPStorer::setSize(
    const int row, const int col) {

    this->row = row;
    this->col = col;
}

void BMPStorer::refactor(int * matrix) {
    unsigned int * nB = new unsigned int[width * height];
    unsigned int * nG = new unsigned int[width * height];
    unsigned int * nR = new unsigned int[width * height];
    for (int i = 0; i < width * height; i++) {
        nB[i] = 0;
        nG[i] = 0;
        nR[i] = 0;
    }
    // 块的宽、高
    int deltaWidth = width / col;
    int deltaHeight = height / row;
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
                        = B[x + preLeftDownPixX + (y + preLeftDownPixY) * newWidth];
                    nG[x + newLeftDownPixX + (y + newLeftDownPixY) * newWidth]
                        = G[x + preLeftDownPixX + (y + preLeftDownPixY) * newWidth];
                    nR[x + newLeftDownPixX + (y + newLeftDownPixY) * newWidth]
                        = R[x + preLeftDownPixX + (y + preLeftDownPixY) * newWidth];
                }
            }
        }
    }
    width = newWidth;
    height = newHeight;
    delete[] B;
    delete[] G;
    delete[] R;
    B = nB;
    G = nG;
    R = nR;
}

void BMPStorer::drawBounds() {
    int deltaWidth = width / col;
    int deltaHeight = height / row;
    // 绘制所有竖线
    for (int c = 1; c < col; c++) {
        for (int y = 0; y < height; y++) {
            B[y * width + c * deltaWidth] = 0;
            G[y * width + c * deltaWidth] = 0;
            R[y * width + c * deltaWidth] = 0;
        }
    }
    // 绘制所有横线
    for (int r = 1; r < row; r++) {
        for (int x = 0; x < width; x++) {
            B[r * deltaHeight * width + x] = 0;
            G[r * deltaHeight * width + x] = 0;
            R[r * deltaHeight * width + x] = 0;
        }
    }
}

void BMPStorer::save(std::ofstream & bmpFile) {
    bmpFile.write(header, 54 * sizeof(char));
    bmpFile.seekp(18, std::ios::beg);
    bmpFile.write((char *)& width, sizeof(int));
    bmpFile.write((char *)& height, sizeof(int));
    bmpFile.seekp(54, std::ios::beg);
    unsigned char c;
    for (int i = 0; i < width * height; i++) {
        c = B[i];
        bmpFile.write((char *)(&c), sizeof(unsigned char));
        c = G[i];
        bmpFile.write((char *)(&c), sizeof(unsigned char));
        c = R[i];
        bmpFile.write((char *)(&c), sizeof(unsigned char));
    }
}
