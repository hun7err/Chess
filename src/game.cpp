#include "../include/game.h"
#include <iostream>

Chess* Game::chess;
bool Game::playing;
QPoint Game::lastPos;

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
    setClicked(false);
    Game::lastPos.setX(-1);
    Game::lastPos.setY(-1);
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
        Figure *f = Game::chess->Board[x*8+y];
    if(f != NULL) {
    if(f->color == 0) {
        switch(f->no) {
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
        switch(f->no) {
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
    }
    }

    //qDebug() << img.isNull();
    if(!(img.isNull())) {
       // cout << "Trying drawImage" << endl;
        //painter.drawImage(QRectF(0.0,0.0,61.0,61.0),img, QRectF(-6.0,0.0,65.0,61.0));
        painter.drawImage(QPoint(7,5),img);
        //this->repaint();
        //painter.Antialiasing = true;
    }
    }
    //this->painter->end();
    //std::cout << "painting" << std::endl;
}

void BoardWidget::mousePressEvent(QMouseEvent *) {
    if(!isClicked()) {
        Figure *f = Game::chess->Board[x*8+y];
        if(f != NULL) {
            this->toggleStyle();
            std::cout << "Adres curPos: " << &((*f).curPos) << std::endl;
            Pawn* p = dynamic_cast<Pawn*>(f);
            std::cout << "(Pawn) curPos addr: " << &((*p).curPos) << std::endl;
            // wboard[j][i]->setToggleStyle(QString("background-color: "+wboard[j][i]->getColor().name()+"; border: 3px solid #FF0090"));
            std::cout << "wywoluje Game::chess->poss_moves([" << f->curPos.x << "," << f->curPos.y << "])" << std::endl;
            vector<Pos> positions = Game::chess->poss_moves(f->curPos);
            for(unsigned int i = 0; i < positions.size(); i++) {
                Pos p = positions[i];
                std::cout << "Possible move: x = " << p.x << ", y = " << p.y << std::endl;
                //Game::getElem(p.y, p.x)->setToggleStyle("background-color: yellow");
                //Game::getElem(p.y, p.x)->toggleStyle();
            }
            setClicked(true);
        }
    }
    //BoardWidget* w = Game::getElem(0,0);
    //w->toggleColor();
    //this->setStyleSheet(QString("background-color: red"));
}

void BoardWidget::setColor(QColor col) {
    fieldColor = col;
    before = QString("background-color: "+fieldColor.name());
}

bool BoardWidget::isClicked() {
    return this->clicked;
}

void BoardWidget::setClicked(bool val) {
    this->clicked = val;
}

const QColor BoardWidget::getColor() {
    return this->fieldColor;
}

void BoardWidget::toggleStyle() {
    QString temp = before;
    before = after;
    after = temp;
    setStyleSheet(before);
}

void BoardWidget::setToggleStyle(QString toggle) {
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
            wboard[j][i]->setPos(i, j);
            if((i % 2 == 0 && j % 2 == 0) || (j % 2 == 1 && i % 2 == 1)) {
                wboard[j][i]->setColor(even);
                wboard[j][i]->setStyleSheet(QString("background-color: "+even.name()));
            } else {
                wboard[j][i]->setColor(odd);
                wboard[j][i]->setStyleSheet(QString("background-color: "+odd.name()));
            }
            wboard[j][i]->setToggleStyle(QString("background-color: "+wboard[j][i]->getColor().name()+"; border: 3px solid #FF0090"));
            wboard[j][i]->setAutoFillBackground(true);
            wboard[j][i]->setVisible(true);
        }
    }
    Game::playing = true;
}
