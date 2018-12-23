#ifndef BMP_STORER
#define BMP_STORER

#include <fstream>

/* ���ڱ��������bmp�ļ� */
class BMPStorer {
public:
    BMPStorer(std::ifstream & bmpFile);
    ~BMPStorer();

    /**
     * ����������
     * @param row: ����
     * @param col: ����
     */
    void setSize(const int row, const int col);


    /**
     * ת��ͼƬʹ���뵱ǰ�����Ӧ
     * @param matrix: ��ǰ����
     */
    void refactor(int * matrix);


    /**
     * ����ÿһС��ı߽�
     */
    void drawBounds();


    /**
     * ����bmp�ļ�
     * @param bmpFile: Ŀ���ļ�
     */
    void save(std::ofstream & bmpFile);

private:
    /* �ļ�ͷ */
    char header[55];

    /* ������ */
    int row;
    int col;

    /* ͼ��Ŀ��� */
    int originWidth;
    int originHeight;
    int drawingWidth;
    int drawingHeight;

    /* ������ɫͨ�� */
    unsigned int * originB;
    unsigned int * originG;
    unsigned int * originR;
    unsigned int * drawingB;
    unsigned int * drawingG;
    unsigned int * drawingR;
};

#endif // !BMP_STORER
