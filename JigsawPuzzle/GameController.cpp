#include "GameController.h"
#include "JigsawPuzzle.h"
#include "Printer.h"

#include <iostream>
#include <cstdio>
#include <conio.h>

GameController::GameController()
    : bmpFileName(""), puzzle(nullptr) {
}

GameController::~GameController() {
    if (puzzle != nullptr) {
        delete puzzle;
    }
}

void GameController::start() {
    printIntroduction();
    setDifficulty();
    puzzle->shuffle();   
    mainLoop();
}

void GameController::mainLoop() {
    Printer printer(puzzle->getRow(), puzzle->getCol());
    printer.printMatrix(puzzle->getMatrix());
    while (true) {     
        if (puzzle->feasibilityAnalysis()) {
            std::cout << "Able to solve!                  "
                << std::endl;
            break;
        }
        else {
            std::cout << "No solution! Press R to restart."
                << std::endl;
            char cmd = _getwch();           
            if (cmd == 'r' || cmd == 'R') {
                puzzle->shuffle();
                printer.printMatrix(puzzle->getMatrix());                
            }
            else {
                break;
            }
        }
    }   
    while (true) {            
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
                    std::cout << "Finish! Press R to play again." 
                        << std::endl;
                }
                break;
            case 'R':
                // restart
                /*
                if (!puzzle->feasibilityAnalysis()
                    || puzzle->isFinished()) {
                    puzzle->shuffle();
                }
                */
                puzzle->restart();
                break;
            case 'G':
                // save image
                break;
            case 'I':
                // save
                break;
            case 'O':
                // load
                break;
            case 'F':
                // auto finish
                break;
            case 'P':
                // exit
                break;
            default:
                break;
            }
            // print  
            printer.printMatrix(puzzle->getMatrix());
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
            continue;
            std::cout << "Invalid input, please try again." 
                << std::endl;
        }
        break;
    }
    puzzle = new JigsawPuzzle(row, col);
}
