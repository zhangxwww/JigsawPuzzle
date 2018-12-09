#ifndef PRINTER
#define PRINTER

class Printer {
public:
    Printer(const int row, const int col);
    ~Printer();
    void printMatrix(int * matrix);
private:
    const int row;
    const int col;
};


#endif // !PRINTER
