#ifndef ARCHIVE
#define ARCHIVE

#include <string>

/* 存档 */
class Archive {
public:
    Archive();
    Archive(const std::string & name,
        const int row, const int col,
        int * matrix);
    ~Archive();

    /* 存档名 */
    const std::string name;

    /* 矩阵的行列 */
    const int row;
    const int col;

    /* 一维数组表示的矩阵 */
    int * matrix;
};

#endif // !ARCHIVE
