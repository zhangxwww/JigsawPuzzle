#ifndef JIGSAW_PUZZLE
#define JIGSAW_PUZZLE

#include <deque>

class Archive;

/* 拼图 */
class JigsawPuzzle {
public:
    JigsawPuzzle(const int row, const int col);
    ~JigsawPuzzle();


    /**
     * 打乱
     */
    void shuffle();


    /**
     * 移动空白格
     * @param c: 移动方向
     * @return : 成功移动则返回true, 否则false
     */
    bool move(const char c);


    /**
     * 反向移动
     * @param c: 移动方向
     * @return : 成功移动则返回true, 否则false
     */
    bool moveBack(const char c);


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


    /**
     * 读档
     * @param archive: 存档
     */
    void loadArchive(const Archive & archive);

    /**
     * 自动完成
     * @return: 路径构成的deque
     */
    std::deque<char> autoFinish();
    
    
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

    /* 当前状态的哈希 */
    long long hash() const;

    /* 计算当前与目标状态的距离 */
    int distance() const;
};

#endif // !JIGSAW_PUZZLE
