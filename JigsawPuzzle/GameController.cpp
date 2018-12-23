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
    // ��ӡ��Ϸ����
    printIntroduction();
    // ����ͼƬ·��
    getBMPfileName();
    // �����Ѷ�
    setDifficulty();
    printer = new Printer(puzzle->getRow(), puzzle->getCol());
    // ����
    puzzle->shuffle();
    // ������Ϸ��ѭ��
    mainLoop();
}

void GameController::mainLoop() {
    // ���ƾ�����վ����µ�����
    printer->clearText();
    printer->printMatrix(puzzle->getMatrix());
    printer->clearText();
    // ����Ƿ��н�
    checkSolvable();
    bool exit = false;
    while (!exit) {
        char cmd;
        /**
         * !!!!!! ����Ŀ�� !!!!!!
         * _kbhit()�� _getch()�Լ������ _getwch()���������ڷ�vs�¿����޷���ȷ����
         * ���Խ����߷ֱ��Ϊ kbhit(), getch()�Լ� getwch()
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
                // �ж��Ƿ���ɸ�ԭ
                if (puzzle->isFinished()) {
                    printer->printText(FINISH);
                }
                break;
            case 'R':
                // restart
                // ����޽⣬�����Ѿ���ɣ����ȴ��ң������¿�ʼ
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
        // ��ǰ״̬�н�
        if (puzzle->feasibilityAnalysis()) {
            printer->printText(SOLVABLE);
            break;
        }
        // �޽⣬����������´���
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
        // ��С�ľ�����û�������
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
    // Ѱ���Ƿ��Ѿ�����ͬ���Ĵ浵
    for (int i = 0; i < ARCHIVES_MAX; i++) {
        if (archives[i] != nullptr
            && archives[i]->name == name) {

            printer->printText(NAME_USED);
            return;
        }
    }
    // �浵�������ARCHIVES_MAX, ��Ḳ������Ĵ浵��������һ������
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
        // Ѱ�Ҹ������ֵĴ浵
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
