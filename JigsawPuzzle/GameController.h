#ifndef GAME_CONTROLLER
#define GAME_CONTROLLER

#include <string>

class JigsawPuzzle;
class Printer;
class Archive;
class BMPStorer;

/* 游戏流程控制 */
class GameController {
public:
    GameController();
    ~GameController();


    /**
     * 开始游戏
     */
    void start();

private:
    /**
     * 游戏的主循环
     */
    void mainLoop();


    /**
     * 检查是否可解，如果不可解会提示玩家，并重新打乱
     */
    void checkSolvable() const;


    /**
     * 打印游戏介绍
     */
    void printIntroduction() const;


    /**
     * 获取bmp图片路径
     */
    void getBMPfileName();


    /**
     * 保存bmp文件
     */
    void saveBMPfile();


    /**
     * 设置难度，提示玩家进行输入
     */
    void setDifficulty();


    /**
     * 存档
     */
    void save();


    /**
     * 读档
     */
    void load();

    /* 拼图 */
    JigsawPuzzle * puzzle;

    /* 用于控制屏幕上显示的内容 */
    Printer * printer;

    /* 用于保存与操作bmp文件 */
    BMPStorer * storer;

    /* 所有的存档 */
    Archive ** archives;

    /* 存档的数量 */
    int archiveCount;

    /* 最多保存的存档数量 */
    static const int ARCHIVES_MAX;
    
    /* 用于输出的一些语句 */
    static const std::string FINISH;
    static const std::string SOLVABLE;
    static const std::string UNSOLVABLE;
    static const std::string ENTER_ARCHIVE_NAME;
    static const std::string SAVED;
    static const std::string NAME_USED;
    static const std::string ARCHIVE_NOT_FOUND;
};

#endif // !GAME_CONTROLLER
