#ifndef GAME_H
#define GAME_H
#include <QWidget>
#include <QColor>

class Game {
    private:
        QWidget *wboard[8][8];  // widget board
        QWidget **parent;
        int width, height;
    public:
        QWidget *getElem(int x, int y);
        void setBoard(QColor even, QColor odd);
        void setWBoardParent(QWidget ** par);
    Game(int w = 61, int h = 61);
    ~Game();
};

#endif // GAME_H
