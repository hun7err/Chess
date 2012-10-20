#include <QApplication>
#include <QGridLayout>
#include "mainwindow.h"
#include "game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Game *game = new Game();
    game->setWBoardParent(&(w.boardwid));
    game->setBoard(QColor("#ffffff"), QColor("#303030"));
    return a.exec();
}
