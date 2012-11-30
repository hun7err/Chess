#ifndef GAME_H
#define GAME_H
#include <QWidget>
#include <QColor>
#include <QPainter>
using namespace std;
#include "chess.h"
#include "mainwindow.h"

class BoardWidget : public QWidget {
    private:
        void paintEvent(QPaintEvent *);
        void mousePressEvent(QMouseEvent *);
        QColor fieldColor;
        QString before;
        QString after;
        bool clicked;
    public:
        int x, y;
        void setColor(QColor col);
        const QColor getColor();
        void toggleStyle();
        void setToggleStyle(QString toggle);
        void setPos(int _x, int _y);
        bool isClicked();
        void setClicked(bool val);
    BoardWidget(QWidget *parent = 0);
    ~BoardWidget();
};

class Colors {
    public:
        static QColor sumColors(const QColor &c1, const QColor &c2);
};

class Game {
    private:
        static BoardWidget* wboard[8][8];  // widget board
        QWidget **parent;
        int width, height;
        static MainWindow *window;
        static QPoint lastPos;
    public:
        static bool playing;
        static Chess* chess;
        static void setLastPos(int x, int y);
        static QPoint getLastPos();
        static BoardWidget* getElem(int x, int y);
        void setBoard(QColor even, QColor odd);
        void setWBoardParent(QWidget ** par);
        void setWindow(MainWindow *win);
        static void newGame();
        static MainWindow* getWindow();
    Game(MainWindow *win, int w = 61, int h = 61);
    ~Game();
};

#endif // GAME_H
