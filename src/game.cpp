#include "../include/game.h"
#include <iostream>

Chess* Game::chess;
bool Game::playing = false;
QPoint Game::lastPos;
MainWindow* Game::window;

BoardWidget* Game::wboard[8][8];
//BoardWidget* Game::getElem(int x, int y) {}

void Game::setWindow(MainWindow *win) {
    window = win;
}

MainWindow* Game::getWindow() {
    return window;
}

Game::Game(MainWindow* win, int w, int h) {
    window = win;
    parent = 0;
    width = w;
    height = h;
    /*Game::chess = new Chess();
    Game::chess->new_game();*/
    chess = NULL;
    //Game::getUi()->curPlayer.setText("test");
    //std::cout << "przed ustawianiem test" << endl;
    //std::cout << "po ustawieniu test" << endl;

    /*
        to-do:
        zrobić coś aby móc stąd zmieniać Ui
    */

    //chess->new_game();
}
Game::~Game() {}

void Game::newGame() {
    chess = new Chess();
    playing = false;
}

void Game::setLastPos(int x, int y) {
    Game::lastPos.setX(x);
    Game::lastPos.setY(y);
}

BoardWidget::BoardWidget(QWidget *parent) : QWidget(parent) {
    setClicked(false);
    Game::setLastPos(-1, -1);
}
BoardWidget::~BoardWidget() {
}

/*

  to-do:
  - fix moves: sometimes the program segfaults and sometimes there are additional figures (so far only knights) spawned (wtf?)
  - fix positions: swap white and black figures (white should be at the bottom, black at the top); things needed to be changed, then:
    1) at Board[] y to 7-y;
    2) at possible_moves y to 7-y

*/

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
    if(!Game::playing) {
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

QColor Colors::sumColors(const QColor &c1, const QColor &c2) {
    QColor ret;
    ret.setRed((c1.red()+c2.red())/2);
    ret.setGreen((c1.green()+c2.green())/2);
    ret.setBlue((c1.blue()+c2.blue())/2);
    return ret;
}

QPoint Game::getLastPos() {
    return Game::lastPos;
}

void BoardWidget::mousePressEvent(QMouseEvent *) {
    std::cout << "[debug] Widget " << x << "," << y << " clicked\n";
    std::cout << "[debug] lastPos: " << Game::getLastPos().x() << "," << Game::getLastPos().y() << std::endl;
    if(!Game::playing) {  // jeśli gra trwa
        Figure *f = Game::chess->Board[x*8+y]; // wybierz figurę na aktualnym polu
        bool moved = false; // nie ruszono (jeszcze) poprzedniej figury
        int _x = Game::getLastPos().x(), _y = Game::getLastPos().y(); // położenie ostatnio wybranej figury
        if(f == NULL || (f!= NULL && f->color != Game::chess->curr_color)) {
            if(_x == x && _y == y) {
                Game::setLastPos(-1,-1);
                //setClicked(false);
            }
            else if(_x != -1 && _y != -1) { // jeśli wybrano już jakąś figurę przed obecnie analizowanym polem...
                Pos p_old(_x,_y), p_new(x,y); // pozycja wybranej wcześniej figury i obecnego pola

                std::cout << "[debug] checking chess->move()" << std::endl;
                vector<Pos> positions = Game::chess->poss_moves(p_old); // sprawdzamy możliwe ruchy
                // wrzucić do ifa od positions
                for (unsigned int i = 0; i < positions.size(); i++) {
                    Pos p2(positions[i]);
                    if(p2.x() == x && p2.y() == y) {
                        if(Game::chess->move(p_old, p_new) != false && !positions.empty()) { // jeśli można się ruszyć
                            std::cout << "[debug] Ruch" << std::endl;
                            Game::getElem(7-_y, _x)->toggleStyle(); // zmień styl pola poprzedniej figury
                            //Game::getElem(_y,_x)->setClicked(false); // nie kliknięto poprzedniego pola
                            Game::getElem(7-y,x)->setClicked(false);
                            moved = true;
                            for(unsigned int i = 0; i < positions.size(); i++) {
                                Pos p2 = positions[i];
                                Game::getElem(7-p2.y(), p2.x())->toggleStyle();
                                //Game::getElem(p2.y(), p2.x())->repaint();
                                Game::getElem(7-p2.y(),p2.x())->setClicked(false);
                            }
                            std::cout << Game::chess->moves.back() << std::endl;
                            //list<string>::iterator it;
                            //for(it = Game::chess->moves[1-Game::chess->curr_color].begin(); it != Game::chess->moves[1-Game::chess->curr_color].end(); it++);
                            //std::cout << *it << std::endl;
                            //std::cout << "curr_color: " << Game::chess->curr_color << std::endl;
                            Game::getWindow()->addHistory(QString(Game::chess->moves.back().c_str()));
                            for(int i = 0; i < 8; i++)
                                for(int j = 0; j < 8; j++)
                                    Game::getElem(i,j)->repaint();
                        } else {
                        }
                        Game::setLastPos(-1, -1);
                    }
                }


                //Game::setLastPos(-1, -1); // reset the last pos.
            }
        } else if (f != NULL && f->color == Game::chess->curr_color && _x != -1 && _y != -1) { // zmiana wybranej figury na inną tego samego koloru
            Pos p_old(_x,_y); // pozycja wybranej wcześniej figury i obecnego pola

            vector<Pos> positions = Game::chess->poss_moves(p_old);
            Game::getElem(7-_y,_x)->toggleStyle(); // zmień styl pola poprzedniej figury
            //Game::getElem(y,x)->toggleStyle();
            setToggleStyle(QString("background-color: "+QColor(255,255,102).name()+"; border: 1px solid black"));
            Game::getElem(7-_y,_x)->setClicked(false); // nie kliknięto poprzedniego pola
            setClicked(true);
            //Game::getElem(y,x)->setClicked(false);
            moved = true;
            for(unsigned int i = 0; i < positions.size(); i++) {
                Pos p2(positions[i]);
                Game::getElem(7-p2.y(), p2.x())->toggleStyle();
                Game::getElem(7-p2.y(), p2.x())->repaint();
                Game::getElem(7-p2.y(),p2.x())->setClicked(false);
            }
            moved = false;
        }
        //std::cout << "Player change" << std::endl;
            Game::getWindow()->playerChange(QString::fromUtf8(Game::chess->curr_color ? "Czarny" : "Biały"));

        if(f != NULL && f->color == Game::chess->curr_color) { // zmiana stylu po wybraniu swojej figury
            //if(!isClicked()) { // if field hasn't been clicked yet
                if(!moved) {
                    this->setToggleStyle(QString("background-color: "+QColor(255,255,102).name()+"; border: 1px solid black"));
                    this->toggleStyle();
                }
                    //std::cout << "Adres curPos: " << &(f->curPos) << std::endl;
                    //std::cout << "(Figure) curPos: x:" << f->curPos.x << ", y:" << f->curPos.y << std::endl;
                    //Pawn* p = dynamic_cast<Pawn*>(f);
                    //p->setPos(0, 0);
                    //std::cout << "(Pawn) curPos addr: " << &(p->curPos) << std::endl;
                    //std::cout << "(Pawn) curPos: x:" << p->curPos.x << ", y:" << p->curPos.y << std::endl;
                    // wboard[j][i]->setToggleStyle(QString("background-color: "+wboard[j][i]->getColor().name()+"; border: 3px solid #FF0090"));
                    //std::cout << "wywoluje Game::chess->poss_moves([" << f->curPos.x << "," << f->curPos.y << "])" << std::endl;
                    QColor c, c_add(0,194,255);
                    vector<Pos> positions = Game::chess->poss_moves(f->curPos);
                    std::cout << "[debug] Possible moves dla f=" << f->no << std::endl;
                    for(unsigned int i = 0; i < positions.size(); i++) {
                        Pos p = positions[i];
                        std::cout << "[debug] Possible move: (" << p.x() << "," << p.y() << ")" << std::endl;
                        QColor field_c = Game::getElem(7-p.y(), p.x())->getColor();
                        c = Colors::sumColors(c_add, field_c);
                        QColor border = Colors::sumColors(QColor(20,20,20),c);
                        //).name()
                        Game::getElem(7-p.y(), p.x())->setToggleStyle("border: 2px solid "+border.name()+"; background-color: "+c.name());
                        Game::getElem(7-p.y(), p.x())->toggleStyle();
                    }
                    Game::setLastPos(x, y);
                setClicked(true);
            //} // if (!isClicked())
        } // if(Game::chess->Board[x*8+y]->color == Game::chess->curr_color)
        if(moved) Game::setLastPos(-1, -1);
    }
    if(!Game::playing) {
    for(int i = 0; i < 64; i++) {
        Figure* f = Game::chess->Board[i];
        if(f == NULL) std::cout << "[ ]";
        else std::cout << "[" << f->no << "]";
        if((i+1) % 8 == 0) std::cout << std::endl;
    }
    /*if(!Game::playing) {
        vector<Pos> positions = Game::chess->figures_to_move();
        for(int i = 0; i < positions.size(); i++) {
            Pos p(positions[i]);
            std::cout << "pos move: (" << p.x() << "," << p.y() << ")" << std::endl;
        }
    }*/
    std::cout << "-----\n"; }
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
            wboard[j][i]->setPos(i, 7-j); // 7-j for good order
            if((i % 2 == 0 && j % 2 == 0) || (j % 2 == 1 && i % 2 == 1)) {
                wboard[j][i]->setColor(even);
                wboard[j][i]->setStyleSheet(QString("background-color: "+even.name()));
            } else {
                wboard[j][i]->setColor(odd);
                wboard[j][i]->setStyleSheet(QString("background-color: "+odd.name()));
            }
            //wboard[j][i]->setToggleStyle(QString("background-color: "+QColor(255,255,102).name()+"; border: 1px solid black"));
            wboard[j][i]->setAutoFillBackground(true);
            wboard[j][i]->setVisible(true);
        }
    }
    Game::playing = true;
}
