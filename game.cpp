#include "game.h"

Game::Game(int w, int h) {
    parent = 0;
    width = w;
    height = h;
}
Game::~Game() {}

QWidget* Game::getElem(int x, int y) {
    return this->wboard[x][y];
}

void Game::setWBoardParent(QWidget **par) {
    parent = par;
}

void Game::setBoard(QColor even, QColor odd) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            wboard[j][i] = new QWidget(*parent);
            wboard[j][i]->setGeometry(i*width,j*height, width, height);
            if((i % 2 == 0 && j % 2 == 0) || (j % 2 == 1 && i % 2 == 1)) {
                wboard[j][i]->setStyleSheet(QString("background-color: "+even.name()));
            } else {
                wboard[j][i]->setStyleSheet(QString("background-color: "+odd.name()));
            }
            wboard[j][i]->setAutoFillBackground(true);
            wboard[j][i]->setVisible(true);
        }
    }
}
