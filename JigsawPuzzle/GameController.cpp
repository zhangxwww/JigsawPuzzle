#include "GameController.h"
#include "JigsawPuzzle.h"
#include "Printer.h"
#include "Archive.h"
#include "BMPStorer.h"

#include <iostream>
#include <fstream>
#include <deque>
#include <cstdio>
#include <conio.h>

GameController::GameController()
    : puzzle(nullptr), printer(nullptr), 
    storer(nullptr), archives(nullptr), 
    archiveCount(0) {

    archives = new Archive * [ARCHIVES_MAX];
    for (int i = 0; i < ARCHIVES_MAX; i++) {
        archives[i] = nullptr;
    }
}

GameController::~GameController() {
    if (puzzle != nullptr) {
        delete puzzle;
    }
    if (printer != nullptr) {
        delete printer;
    }
    if (archives != nullptr) {
        for (int i = 0; i < ARCHIVES_MAX; i++) {
            if (archives[i] != nullptr) {
                delete archives[i];
            }
        }
        delete[] archives;
    }
    if (storer != nullptr) {
        delete storer;
    }
}

void GameController::start() {
    // 打印游戏介绍
    printIntroduction();
    // 输入图片路径
    getBMPfileName();
    // 设置难度
    setDifficulty();
    printer = new Printer(puzzle->getRow(), puzzle->getCol());
    // 打乱
    puzzle->shuffle();
    // 进入游戏主循环
    mainLoop();
}

void GameController::mainLoop() {
    // 绘制矩阵，清空矩阵下的文字
    printer->clearText();
    printer->printMatrix(puzzle->getMatrix());
    printer->clearText();
    // 检查是否有解
    checkSolvable();
    bool exit = false;
    while (!exit) {
        char cmd;
        /**
         * !!!!!! 【醒目】 !!!!!!
         * _kbhit()与 _getch()以及后面的 _getwch()几个函数在非vs下可能无法正确编译
         * 可以将二者分别改为 kbhit(), getch()以及 getwch()
         */
        if (_kbhit()) {
            cmd = _getch();
            if (cmd >= 'a' && cmd <= 'z') {
                cmd = cmd - 'a' + 'A';
            }
            switch (cmd) {
            case 'W':
            case 'A':
            case 'S':
            case 'D':
                // move
                puzzle->move(cmd);
                printer->clearText();
                // print  
                printer->printMatrix(puzzle->getMatrix());
                // 判断是否完成复原
                if (puzzle->isFinished()) {
                    printer->printText(FINISH);
                }
                break;
            case 'R':
                // restart
                // 如果无解，或是已经完成，则先打乱，再重新开始
                if (!puzzle->feasibilityAnalysis()
                    || puzzle->isFinished()) {
                    puzzle->shuffle();
                    checkSolvable();
                }
                puzzle->restart();
                // print  
                printer->printMatrix(puzzle->getMatrix());
                break;
            case 'G':
                // save image
                saveBMPfile();
                break;
            case 'I':
                // save
                save();
                break;
            case 'O':
                // load
                load();
                // print  
                printer->printMatrix(puzzle->getMatrix());
                break;
            case 'F':
                // auto finish
                printer->printPath(puzzle->autoFinish());
                break;
            case 'P':
                // exit
                exit = true;
                break;
            default:
                break;
            }
            
        }
    }
}

void GameController::checkSolvable() const {
    printer->printMatrix(puzzle->getMatrix());
    while (true) {
        // 当前状态有解
        if (puzzle->feasibilityAnalysis()) {
            printer->printText(SOLVABLE);
            break;
        }
        // 无解，按任意键重新打乱
        else {
            printer->printText(UNSOLVABLE);
            char cmd = _getwch();
            puzzle->shuffle();
            printer->printMatrix(puzzle->getMatrix());
        }
    }
}

void GameController::printIntroduction() const {
    std::cout << "Welcome to Jigsaw puzzle!" << std::endl
        << "Press WASD to move" << std::endl
        << "Press R to restart" << std::endl
        << "Press G to save current image" << std::endl
        << "Press I to save current progress" << std::endl
        << "Press O to load previous progress" << std::endl
        << "Press F to auto finish" << std::endl
        << "Press P to exit" << std::endl;
}

void GameController::getBMPfileName() {
    std::cout << "Please enter the bmp file name :" << std::endl;
    std::ifstream bmpFile;
    std::string bmpFileName;
    while (true) {
        std::cin >> bmpFileName;
        bmpFile.open(bmpFileName, std::ios::binary);
        if (bmpFile) {
            break;
        }
        std::cout << "File not found, please try again." << std::endl;
    }
    storer = new BMPStorer(bmpFile);
    bmpFile.close();
}

void GameController::saveBMPfile() {
    std::cout << "Please enter the file name :" << std::endl;
    std::ofstream bmpFile;
    std::string bmpFileName;
    while (true) {
        std::cin >> bmpFileName;
        bmpFile.open(bmpFileName, std::ios::out | std::ios::binary);
        if (bmpFile) {
            break;
        }
        std::cout << "Can't save the image, please try again." << std::endl;
    }
    storer->refactor(puzzle->getMatrix());
    storer->drawBounds();
    storer->save(bmpFile);
    bmpFile.close();
}

void GameController::setDifficulty() {
    int row;
    int col;
    while (true) {
        std::cout << "Please enter rows : ";
        std::cin >> row;
        std::cout << "Please enter columns : ";
        std::cin >> col;
        // 过小的矩阵是没有意义的
        if (row < 2 || col < 2 || row * col < 6) {
            std::cout << "Invalid input, please try again."
                << std::endl;
            continue;
        }
        break;
    }
    puzzle = new JigsawPuzzle(row, col);
    storer->setSize(row, col);
}

void GameController::save() {
    printer->printText(ENTER_ARCHIVE_NAME);
    std::string name;
    std::cin >> name;
    // 寻找是否已经存在同名的存档
    for (int i = 0; i < ARCHIVES_MAX; i++) {
        if (archives[i] != nullptr
            && archives[i]->name == name) {

            printer->printText(NAME_USED);
            return;
        }
    }
    // 存档如果超过ARCHIVES_MAX, 则会覆盖最早的存档，类似于一个队列
    if (archives[archiveCount % ARCHIVES_MAX] != nullptr) {
        delete archives[archiveCount % ARCHIVES_MAX];
        archives[archiveCount % ARCHIVES_MAX] = nullptr;
    }
    archives[archiveCount % ARCHIVES_MAX] = 
        new Archive(name, puzzle->getRow(), 
            puzzle->getCol(), puzzle->getMatrix());
    archiveCount++;
    printer->printText(SAVED);
}

void GameController::load() {
    printer->printText(ENTER_ARCHIVE_NAME);
    std::string name;
    std::cin >> name;
    bool found = false;
    for (int i = 0; i < ARCHIVES_MAX; i++) {
        // 寻找给定名字的存档
        if (archives[i] != nullptr 
            && archives[i]->name == name) {

            if (puzzle != nullptr) {
                delete puzzle;
                puzzle = nullptr;
            }
            puzzle = new JigsawPuzzle(*archives[i]);
            found = true;
            break;
        }
    }
    if (!found) {
        printer->printText(ARCHIVE_NOT_FOUND);
    }
}

const int GameController::ARCHIVES_MAX = 5;

const std::string GameController::FINISH             = "Finish! Press R to play again.            ";
const std::string GameController::SOLVABLE           = "Able to solve!                            ";
const std::string GameController::UNSOLVABLE         = "No solution! Press any key to restart.    ";
const std::string GameController::ENTER_ARCHIVE_NAME = "Please enter the name:                    ";
const std::string GameController::SAVED              = "Saved successfully!                       ";
const std::string GameController::ARCHIVE_NOT_FOUND  = "Archive not found. Please check your name.";
const std::string GameController::NAME_USED          = "This name has already been used.          ";
