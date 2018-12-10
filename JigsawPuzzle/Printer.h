#ifndef PRINTER
#define PRINTER

#include <string>

/* ������Ļ����Ϣ�Ĵ�ӡ */
class Printer {
public:
    Printer(const int row, const int col);
    ~Printer();

    /** 
     * ��ƴͼ�Ծ�����ʽ��ӡ����Ļ��
     * @param matrix: ����ӡ�ľ���
     */
    void printMatrix(int * matrix);


    /**
     * �ھ����·���ӡ����
     * @param text: ����ӡ������
     */
    void printText(const std::string & text);


    /**
     * ��վ����·�������
     */
    void clearText();
private:
    /* ��������� */
    const int row;
    const int col;
};

#endif // !PRINTER
