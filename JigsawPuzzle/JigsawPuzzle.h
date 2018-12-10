#ifndef JIGSAW_PUZZLE
#define JIGSAW_PUZZLE

class Archive;

class JigsawPuzzle {
public:
    JigsawPuzzle(const int row, const int col);
    JigsawPuzzle(const Archive & archive);
    ~JigsawPuzzle();

    void shuffle();
    void move(const char c);
    bool isFinished() const;
    void restart();
    
    bool feasibilityAnalysis() const;
    /*
    void autoFinish()
    */
    int * getMatrix() const;
    const int getRow() const;
    const int getCol() const;

private:
    const int row;
    const int col;

    int * matrix;
    int * originMatrix;
    int curBlankRow;
    int curBlankCol;
};

#endif // !JIGSAW_PUZZLE
