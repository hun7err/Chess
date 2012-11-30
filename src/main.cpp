#include <QApplication>
#include "../include/mainwindow.h"
#include "../include/game.h"
#include "../include/includes.h"
#include <QPainter>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    // wydzielić to do plik->Nowa gra
    Game *game = new Game(&w);
    game->setWBoardParent(&(w.boardwid));		// set widget board parent
    game->setBoard(QColor("#ffffff"), QColor("#303030"));	// setBoard(evenColor, oddColor) - even = even at 8 (or a8), odd respectively to that
    //game->newGame();
    //game->getElem(0, 0);
    //QPainter painter(game->getElem(0, 0));

    return a.exec();
}
