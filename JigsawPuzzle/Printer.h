#ifndef PRINTER
#define PRINTER

#include <string>
#include <deque>

/* 用于屏幕上信息的打印 */
class Printer {
public:
    Printer(const int row, const int col);
    ~Printer();

    /** 
     * 将拼图以矩阵形式打印在屏幕上
     * @param matrix: 待打印的矩阵
     */
    void printMatrix(int * matrix);


    /**
     * 在矩阵下方打印文字
     * @param text: 待打印的文字
     */
    void printText(const std::string & text);


    /**
     * 在矩阵下方打印自动完成的步骤
     * @param path: 待打印的步骤
     */
    void printPath(std::deque<char> path);


    /**
     * 清空矩阵下方的文字
     */
    void clearText();
private:
    /* 矩阵的行列 */
    const int row;
    const int col;
};

#endif // !PRINTER
