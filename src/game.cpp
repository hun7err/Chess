#include "../include/game.h"
#include <iostream>

Chess* Game::chess;
bool Game::playing;
BoardWidget* Game::wboard[8][8];
//BoardWidget* Game::getElem(int x, int y) {}

Game::Game(int w, int h) {
    parent = 0;
    width = w;
    height = h;
    /*Game::chess = new Chess();
    Game::chess->new_game();*/
    chess = new Chess();
    playing = false;
    //chess->new_game();
}
Game::~Game() {}

BoardWidget::BoardWidget(QWidget *parent) : QWidget(parent) {
}
BoardWidget::~BoardWidget() {
}

void BoardWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QImage img;
    //this->painter->begin(this);

    /*cout << "Board: ";
    for(int i = 0; i < 64; i++)
        if(Game::chess->Board[i] != NULL)
            cout << Game::chess->Board[i]->no << "(c" << Game::chess->Board[i]->color << " x" << Game::chess->Board[i]->curPos.x <<" y" << Game::chess->Board[i]->curPos.y << ") ";
        else
            cout << "[NULL] ";
    cout << endl;*/

    //cout << "Checking field val" << endl;
    if(Game::playing) {
       // cout << "Playing, checking color. Pos: x = " << x << ", y = " << y << endl;
#define BOARD
#ifdef BOARD
        Figure *f = new Figure();
#else
        Figure f;
#endif
        //for(int i = 0; i < 32; i++) {
#ifdef BOARD
            /*if( Game::chess->Board[64+i]->curPos.x == x && Game::chess->Board[64+i]->curPos.y == y && Game::chess->Board[64+i]->alive) {
                f = Game::chess->Board[64+i];
                break;
            }*/
#else
            if(Game::chess->Set[i].curPos.x == x && Game::chess->Set[i].curPos.y == y) {
                f = Game::chess->Set[i];
            }

#endif
        //}
        f = Game::chess->Board[x*8+y];
        if(f != NULL)
#ifdef BOARD
    if(f->color == 0) {
#else
        if(f.color == 0) {
#endif
        //cout << "Before switch, x = " << x << ", y = " << y << endl;
#ifdef BOARD
        switch(f->no) {
#else
            switch(f.no) {
#endif
            case KING:
                img.load(":/images/k1.png");
                break;
            case PAWN:
                img.load(":/images/p1.png");
                break;
            case ROOK:
                img.load(":/images/w1.png");
                break;
            case BISHOP:
                img.load(":/images/g1.png");
                break;
            case KNIGHT:
                img.load(":/images/s1.png");
                break;
            case QUEEN:
                img.load(":/images/h1.png");
                break;
        }
    } else {
        //cout << "in else{}" << endl;
#ifdef BOARD
        switch(f->no) {
#else
            switch(f.no) {
#endif
            case KING:
                img.load(":/images/k2.png");
                break;
            case PAWN:
                img.load(":/images/p2.png");
                break;
            case ROOK:
                img.load(":/images/w2.png");
                break;
            case BISHOP:
                img.load(":/images/g2.png");
                break;
            case KNIGHT:
                img.load(":/images/s2.png");
                break;
            case QUEEN:
                img.load(":/images/h2.png");
                break;
        }
        /*switch(Game::chess->Board[x*g+y]->no) {

        }*/
    }
    }
    //cout << "img: " << img.isNull() << endl;

    //qDebug() << img.isNull();
    if(!(img.isNull())) {
       // cout << "Trying drawImage" << endl;
        //painter.drawImage(QRectF(0.0,0.0,61.0,61.0),img, QRectF(-6.0,0.0,65.0,61.0));
        painter.drawImage(QPoint(7,5),img);
        //this->repaint();
        //painter.Antialiasing = true;
    }
    //this->painter->end();
    //std::cout << "painting" << std::endl;
}

void BoardWidget::mousePressEvent(QMouseEvent *) {
    this->toggleColor();
    BoardWidget* w = Game::getElem(0,0);
    w->toggleColor();
    //this->setStyleSheet(QString("background-color: red"));
}

void BoardWidget::setColor(QColor col) {
    fieldColor = col;
}

void BoardWidget::toggleColor() {
    QColor c = before;
    before = after;
    after = c;
    setStyleSheet(QString("background-color: "+fieldColor.name()));

}

void BoardWidget::setToggleColor(QColor toggle) {
    after = toggle;
}

BoardWidget* Game::getElem(int x, int y) {
    return Game::wboard[x][y];
}

void BoardWidget::setPos(int _x, int _y) {
    x = _x;
    y = _y;
}

void Game::setWBoardParent(QWidget **par) {
    parent = par;
}

void Game::setBoard(QColor even, QColor odd) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            wboard[j][i] = new BoardWidget(*parent);
            wboard[j][i]->setGeometry(i*width,j*height, width, height);
            wboard[j][i]->setToggleColor(QColor("#1111ff"));
            wboard[j][i]->setPos(i, j);
            if((i % 2 == 0 && j % 2 == 0) || (j % 2 == 1 && i % 2 == 1)) {
                wboard[j][i]->setColor(even);
                wboard[j][i]->setStyleSheet(QString("background-color: "+even.name()));
            } else {
                wboard[j][i]->setColor(odd);
                wboard[j][i]->setStyleSheet(QString("background-color: "+odd.name()));
            }
            wboard[j][i]->setAutoFillBackground(true);
            wboard[j][i]->setVisible(true);
        }
    }
    Game::playing = true;
}
