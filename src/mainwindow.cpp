#include "../include/mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QObject>
#include <QListWidgetItem>
#include <QTimer>
#include <QTime>
#include <iostream>
#include "../include/game.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateCaption()));
    //QTimer* timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(updateCaption()));
    //timer->start(1000);

    ui->setupUi(this);
    QObject::connect(this, SIGNAL(setCurPlayer(QString)), this, SLOT(setCurrentPlayer(QString)));
    QObject::connect(this, SIGNAL(addHistItem(QString)), this, SLOT(addHistoryItem(QString)));
    QObject::connect(
        ui->listWidget->model(),
        SIGNAL(rowsInserted ( const QModelIndex &, int, int ) ),
        ui->listWidget,
        SLOT(scrollToBottom ())
    ); // a magic trick to scroll down. Do not touch.
    cur_player = 0;
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

void MainWindow::updateCaption() {
    QTime t;
    if(cur_player == 0)
        t = QTime::fromString(ui->Time0->text(), "mm:ss");
    else
        t = QTime::fromString(ui->Time1->text(), "mm:ss");
    //= QTime::fromString(ui->BlackTime->text(), "mm:ss");
    //t.addSecs(1);
    t = t.addSecs(-1);
    std::cout << "Time update: " << t.toString("mm:ss").toStdString() << std::endl;
    if(cur_player == 0)
        ui->Time0->setText(t.toString("mm:ss"));
    else
        ui->Time1->setText(t.toString("mm:ss"));
}

void MainWindow::playerChange(const QString &q) {
    emit setCurPlayer(q);
}

void MainWindow::addHistory(const QString &q) {
    emit addHistItem(q);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionWyjd_triggered() {
    this->destroy();
    exit(0);
}

void MainWindow::setCurrentPlayer(const QString &q) {
    this->ui->curPlayer->setText(q);
}

void MainWindow::on_actionNowa_gra_triggered()
{
    if(timer->isActive()) timer->stop();
    Game::newGame();
    ui->listWidget->clear();
    this->setCurrentPlayer(QString::fromUtf8("Biały"));
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            Game::getElem(i,j)->repaint();
    timer->start(1000);

    /*
        to-do:
        - wyrzucić metody stopujące i startujące timer do publica
        - sprawdzanie pola na starcie i uniemożliwiwanie ruchu
        - sprawdzanie stanu gry i messagebox+stopowanie jak pat/mat
        - okno do ustawiania czasu trwania partii (odpowiedni komponent Qt)
    */

    //std::cout << "Nowa gra" << std::endl;
}

void MainWindow::on_pushButton_clicked()
{
    // wyrzucić do ruchu figurą; wtedy stopować timer i startować z interwałem 1000ms
    // (no i wywalić ten przycisk :p)
    timer->stop();
    cur_player = (cur_player+1)%2;
    timer->start(1000);
    //ui->listWidget->addItem(QString("test"+QString::number(ui->listWidget->count()+1)));
    //if(timer->isActive()) timer->stop();
    //else timer->start(1000);
    //ui->listWidget->itemAt(ui->listWidget->count()-1)-
}

void MainWindow::addHistoryItem(const QString &q) {
    ui->listWidget->addItem(QString::number(ui->listWidget->count()+1)+". "+q);
}

void MainWindow::on_actionCofnij_triggered()
{
    timer->stop();
    Game::chess->undo();
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            Game::getElem(i,j)->repaint();
    timer->start(1000);
}
