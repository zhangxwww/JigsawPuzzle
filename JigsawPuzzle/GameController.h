#ifndef GAME_CONTROLLER
#define GAME_CONTROLLER

#include <string>

class JigsawPuzzle;
class Printer;
class Archive;

/* ��Ϸ���̿��� */
class GameController {
public:
    GameController();
    ~GameController();


    /**
     * ��ʼ��Ϸ
     */
    void start();

private:
    /**
     * ��Ϸ����ѭ��
     */
    void mainLoop();


    /**
     * ����Ƿ�ɽ⣬������ɽ����ʾ��ң������´���
     */
    void checkSolvable() const;


    /**
     * ��ӡ��Ϸ����
     */
    void printIntroduction() const;

    // TODO read bmp


    /**
     * �����Ѷȣ���ʾ��ҽ�������
     */
    void setDifficulty();


    /**
     * �浵
     */
    void save();


    /**
     * ����
     */
    void load();

    /* BMPͼƬ��·�� */
    std::string bmpFileName;

    /* ƴͼ */
    JigsawPuzzle * puzzle;

    /* ���ڿ�����Ļ����ʾ������ */
    Printer * printer;

    /* ���еĴ浵 */
    Archive ** archives;

    /* �浵������ */
    int archiveCount;

    /* ��ౣ��Ĵ浵���� */
    static const int ARCHIVES_MAX;
    
    /* ���������һЩ��� */
    static const std::string FINISH;
    static const std::string SOLVABLE;
    static const std::string UNSOLVABLE;
    static const std::string ENTER_ARCHIVE_NAME;
    static const std::string SAVED;
    static const std::string NAME_USED;
    static const std::string ARCHIVE_NOT_FOUND;
};

#endif // !GAME_CONTROLLER
