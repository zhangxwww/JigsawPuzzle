#ifndef GAME_CONTROLLER
#define GAME_CONTROLLER

#include <string>

class JigsawPuzzle;

class GameController {
public:
    GameController();
    ~GameController();

    void start();

private:
    void mainLoop();
    void printIntroduction() const;
    // read bmp
    void setDifficulty();

    std::string bmpFileName;
    JigsawPuzzle * puzzle;
};

#endif // !GAME_CONTROLLER
