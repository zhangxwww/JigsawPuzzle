#ifndef JIGSAW_PUZZLE
#define JIGSAW_PUZZLE

class Archive;

/* ƴͼ */
class JigsawPuzzle {
public:
    JigsawPuzzle(const int row, const int col);
    JigsawPuzzle(const Archive & archive);
    ~JigsawPuzzle();


    /**
     * ����
     */
    void shuffle();


    /**
     * �ƶ��հ׸�
     * @param c: �ƶ�����
     */
    void move(const char c);


    /**
     * �Ƿ���ɸ�ԭ
     * @return: ��ɸ�ԭ����true, ����false
     */
    bool isFinished() const;


    /**
     * ���¿�ʼ���������´���
     */
    void restart();
    

    /**
     * �жϵ�ǰ״̬�Ƿ��н�
     * @return: �н��򷵻�true, ����false
     */
    bool feasibilityAnalysis() const;


    /* TODO
    void autoFinish()
    */


    int * getMatrix() const;
    const int getRow() const;
    const int getCol() const;

private:
    /* ��������� */
    const int row;
    const int col;

    /* һά�����ʾ�ľ��� */
    int * matrix;

    /* ���δ�ƶ����ľ����������¿�ʼʱ�ص���ԭʼ��״̬ */
    int * originMatrix;

    /* ��ǰ�հ׸��������� */
    int curBlankRow;
    int curBlankCol;
};

#endif // !JIGSAW_PUZZLE
