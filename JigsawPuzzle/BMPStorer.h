#ifndef BMP_STORER
#define BMP_STORER

#include <fstream>

class BMPStorer {
public:
    BMPStorer(std::ifstream & bmpFile);
    ~BMPStorer();

    void setSize(const int row, const int col);
    void refactor(int * matrix);
    void drawBounds();
    void save(std::ofstream & bmpFile);

private:
    char header[55];
    int row;
    int col;
    int width;
    int height;
    unsigned int * B;
    unsigned int * G;
    unsigned int * R;
};

#endif // !BMP_STORER
