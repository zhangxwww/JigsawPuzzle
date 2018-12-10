#include "GameController.h"
#include "JigsawPuzzle.h"
#include "Printer.h"
#include "Archive.h"

#include <iostream>
#include <cstdio>
#include <conio.h>

GameController::GameController()
    : bmpFileName(""), puzzle(nullptr),
    printer(nullptr), archives(nullptr),
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
}

void GameController::start() {
    printIntroduction();
    setDifficulty();
    printer = new Printer(puzzle->getRow(), puzzle->getCol());
    puzzle->shuffle();
    mainLoop();
}

void GameController::mainLoop() {
    printer->printMatrix(puzzle->getMatrix());
    printer->clearText();
    checkSolvable();
    bool exit = false;
    while (!exit) {
        char cmd;
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
                if (puzzle->isFinished()) {
                    printer->printText(FINISH);
                }
                break;
            case 'R':
                // restart             
                if (!puzzle->feasibilityAnalysis()
                    || puzzle->isFinished()) {
                    puzzle->shuffle();
                    checkSolvable();
                }
                puzzle->restart();
                break;
            case 'G':
                // save image
                break;
            case 'I':
                // save
                save();
                break;
            case 'O':
                // load
                break;
            case 'F':
                // auto finish
                break;
            case 'P':
                // exit
                exit = true;
                break;
            default:
                break;
            }
            // print  
            printer->printMatrix(puzzle->getMatrix());
        }
    }
}

void GameController::checkSolvable() const {
    printer->printMatrix(puzzle->getMatrix());
    while (true) {
        if (puzzle->feasibilityAnalysis()) {
            printer->printText(SOLVABLE);
            break;
        }
        else {
            printer->printText(UNSOLVABLE);
            char cmd = _getwch();
            puzzle->shuffle();
            printer->printMatrix(puzzle->getMatrix());
        }
    }
}

void GameController::printIntroduction() const {
    // TODO
}

void GameController::setDifficulty() {
    int row;
    int col;
    while (true) {
        std::cout << "Please enter rows : ";
        std::cin >> row;
        std::cout << "Please enter columns : ";
        std::cin >> col;
        if (row < 2 || col < 2 || row * col < 6) {
            std::cout << "Invalid input, please try again."
                << std::endl;
            continue;
        }
        break;
    }
    puzzle = new JigsawPuzzle(row, col);
}

void GameController::save() {
    // printer->clearText();
    // std::cout << "Please enter the name: ";
    printer->printText(ENTER_ARCHIVE_NAME);
    std::string name;
    std::cin >> name;
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

const std::string GameController::FINISH = "Finish! Press R to play again.";
const std::string GameController::SOLVABLE = "Able to solve!                        ";
const std::string GameController::UNSOLVABLE = "No solution! Press any key to restart.";
const std::string GameController::ENTER_ARCHIVE_NAME = "Please enter the name: ";
const std::string GameController::SAVED = "Saved successfully!";
const int GameController::ARCHIVES_MAX = 5;
