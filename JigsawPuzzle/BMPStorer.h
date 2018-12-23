#ifndef BMP_STORER
#define BMP_STORER

#include <fstream>

/* 用于保存与操作bmp文件 */
class BMPStorer {
public:
    BMPStorer(std::ifstream & bmpFile);
    ~BMPStorer();

    /**
     * 设置行列数
     * @param row: 行数
     * @param col: 列数
     */
    void setSize(const int row, const int col);


    /**
     * 转化图片使其与当前矩阵对应
     * @param matrix: 当前矩阵
     */
    void refactor(int * matrix);


    /**
     * 绘制每一小块的边界
     */
    void drawBounds();


    /**
     * 保存bmp文件
     * @param bmpFile: 目标文件
     */
    void save(std::ofstream & bmpFile);

private:
    /* 文件头 */
    char header[55];

    /* 行列数 */
    int row;
    int col;

    /* 图像的宽、高 */
    int originWidth;
    int originHeight;
    int drawingWidth;
    int drawingHeight;

    /* 三个颜色通道 */
    unsigned int * originB;
    unsigned int * originG;
    unsigned int * originR;
    unsigned int * drawingB;
    unsigned int * drawingG;
    unsigned int * drawingR;
};

#endif // !BMP_STORER
