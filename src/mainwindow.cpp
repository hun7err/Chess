#include "../include/mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QObject>
#include <iostream>
#include "../include/game.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(this, SIGNAL(setCurPlayer(QString)), this, SLOT(setCurrentPlayer(QString)));
    boardwid = new QWidget(this);
    boardwid->setGeometry(18, 45, 8*61, 8*61);
    boardwid->setStyleSheet(QString("background-color: #000000; border: 1px solid black"));
    boardwid->setAutoFillBackground(true);
    boardwid->setVisible(true);
    for (int i = 0; i < 8; i++) {   // board generation
        QLabel *label1 = new QLabel(), *label2 = new QLabel();
        label1->setParent(this);
        label2->setParent(this);
        label1->setGeometry(18+i*61,28,61,15);
        label2->setGeometry(2,45+i*61,15,61);
        label1->setText(QString('A'+i));
        label2->setText(QString('8'-i));
        label1->setStyleSheet("font-weight: bold");
        label2->setStyleSheet("font-weight: bold");
        label1->setAlignment(Qt::AlignCenter);
        label2->setAlignment(Qt::AlignHCenter|Qt::AlignCenter);
        label1->setVisible(true);
        label2->setVisible(true);
    }
}

void MainWindow::playerChange(const QString &q) {
    emit setCurPlayer(q);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionWyjd_triggered()
{
    this->destroy();
    exit(0);
}

void MainWindow::setCurrentPlayer(const QString &q) {
    this->ui->curPlayer->setText(q);
}

void MainWindow::on_actionNowa_gra_triggered()
{
    Game::newGame();
    this->setCurrentPlayer(QString::fromUtf8("Biały"));
    for(int i = 0; i < 8; i++)
        for(int c = 0; c < 2; c++)
            for(int j = 0; j < 2; j++)
                    Game::getElem(j+c*6, i)->repaint();
    //std::cout << "Nowa gra" << std::endl;
}
