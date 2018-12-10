#ifndef GAME_CONTROLLER
#define GAME_CONTROLLER

#include <string>

class JigsawPuzzle;
class Printer;
class Archive;

class GameController {
public:
    GameController();
    ~GameController();

    void start();

private:
    void mainLoop();
    void checkSolvable() const;
    void printIntroduction() const;
    // read bmp
    void setDifficulty();
    void save();
    void load();

    std::string bmpFileName;
    JigsawPuzzle * puzzle;
    Printer * printer;
    Archive ** archives;
    int archiveCount;

    static const std::string FINISH;
    static const std::string SOLVABLE;
    static const std::string UNSOLVABLE;
    static const std::string ENTER_ARCHIVE_NAME;
    static const std::string SAVED;
    static const std::string NAME_USED;
    static const std::string ARCHIVE_NOT_FOUND;
    static const int ARCHIVES_MAX;
};

#endif // !GAME_CONTROLLER
