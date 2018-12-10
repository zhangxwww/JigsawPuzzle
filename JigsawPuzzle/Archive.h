#ifndef ARCHIVE
#define ARCHIVE

#include <string>

/* �浵 */
class Archive {
public:
    Archive();
    Archive(const std::string & name,
        const int row, const int col,
        int * matrix);
    ~Archive();

    /* �浵�� */
    const std::string name;

    /* ��������� */
    const int row;
    const int col;

    /* һά�����ʾ�ľ��� */
    int * matrix;
};

#endif // !ARCHIVE
