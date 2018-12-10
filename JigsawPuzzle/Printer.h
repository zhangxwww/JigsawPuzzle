#ifndef PRINTER
#define PRINTER

#include <string>

class Printer {
public:
    Printer(const int row, const int col);
    ~Printer();
    void printMatrix(int * matrix);
    void printText(const std::string & text);
    void clearText();
private:
    const int row;
    const int col;
};

#endif // !PRINTER
