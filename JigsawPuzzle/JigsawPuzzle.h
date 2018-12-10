#ifndef JIGSAW_PUZZLE
#define JIGSAW_PUZZLE

class Archive;

/* 拼图 */
class JigsawPuzzle {
public:
    JigsawPuzzle(const int row, const int col);
    JigsawPuzzle(const Archive & archive);
    ~JigsawPuzzle();


    /**
     * 打乱
     */
    void shuffle();


    /**
     * 移动空白格
     * @param c: 移动方向
     */
    void move(const char c);


    /**
     * 是否完成复原
     * @return: 完成复原返回true, 否则false
     */
    bool isFinished() const;


    /**
     * 重新开始，但不重新打乱
     */
    void restart();
    

    /**
     * 判断当前状态是否有解
     * @return: 有解则返回true, 否则false
     */
    bool feasibilityAnalysis() const;


    /* TODO
    void autoFinish()
    */


    int * getMatrix() const;
    const int getRow() const;
    const int getCol() const;

private:
    /* 矩阵的行列 */
    const int row;
    const int col;

    /* 一维数组表示的矩阵 */
    int * matrix;

    /* 玩家未移动过的矩阵，用于重新开始时回到最原始的状态 */
    int * originMatrix;

    /* 当前空白格所在行列 */
    int curBlankRow;
    int curBlankCol;
};

#endif // !JIGSAW_PUZZLE
