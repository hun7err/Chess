#ifndef GAME_H
#define GAME_H
#include <QWidget>
#include <QColor>
#include <QPainter>
using namespace std;
#include "chess.h"

class BoardWidget : public QWidget {
    private:
        void paintEvent(QPaintEvent *);
        void mousePressEvent(QMouseEvent *);
    public:
        int x, y;
        QColor fieldColor;
        QColor before;
        QColor after;
        void setColor(QColor col);
        void toggleColor();
        void setToggleColor(QColor toggle);
        void setPos(int _x, int _y);
    BoardWidget(QWidget *parent = 0);
    ~BoardWidget();
};

class Game {
    private:
        static BoardWidget* wboard[8][8];  // widget board
        QWidget **parent;
        int width, height;
    public:
        static bool playing;
        static Chess* chess;
        //BoardWidget *getElem(int x, int y);
        static BoardWidget *getElem(int x, int y);
        void setBoard(QColor even, QColor odd);
        void setWBoardParent(QWidget ** par);
    Game(int w = 61, int h = 61);
    ~Game();
};

#endif // GAME_H
