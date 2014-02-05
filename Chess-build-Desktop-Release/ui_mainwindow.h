/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu Dec 6 12:28:04 2012
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionWyjd;
    QAction *actionNowa_gra;
    QAction *actionCofnij;
    QAction *actionO_programie;
    QWidget *centralWidget;
    QGroupBox *groupBox_2;
    QLabel *curPlayer;
    QGroupBox *groupBox_3;
    QLabel *label_2;
    QLabel *Time0;
    QLabel *Time1;
    QLabel *label;
    QGroupBox *groupBox;
    QListWidget *listWidget;
    QMenuBar *menuBar;
    QMenu *menuPlik;
    QMenu *menuEdycja;
    QMenu *menuPomoc;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(741, 575);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actionWyjd = new QAction(MainWindow);
        actionWyjd->setObjectName(QString::fromUtf8("actionWyjd"));
        actionNowa_gra = new QAction(MainWindow);
        actionNowa_gra->setObjectName(QString::fromUtf8("actionNowa_gra"));
        actionCofnij = new QAction(MainWindow);
        actionCofnij->setObjectName(QString::fromUtf8("actionCofnij"));
        actionO_programie = new QAction(MainWindow);
        actionO_programie->setObjectName(QString::fromUtf8("actionO_programie"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(530, 10, 201, 80));
        curPlayer = new QLabel(groupBox_2);
        curPlayer->setObjectName(QString::fromUtf8("curPlayer"));
        curPlayer->setGeometry(QRect(36, 30, 131, 31));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        curPlayer->setFont(font);
        curPlayer->setAlignment(Qt::AlignCenter);
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(530, 100, 201, 91));
        groupBox_3->setFlat(false);
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(110, 30, 71, 16));
        label_2->setAlignment(Qt::AlignCenter);
        Time0 = new QLabel(groupBox_3);
        Time0->setObjectName(QString::fromUtf8("Time0"));
        Time0->setGeometry(QRect(16, 50, 81, 31));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        Time0->setFont(font1);
        Time0->setAlignment(Qt::AlignCenter);
        Time1 = new QLabel(groupBox_3);
        Time1->setObjectName(QString::fromUtf8("Time1"));
        Time1->setGeometry(QRect(100, 50, 91, 31));
        Time1->setFont(font1);
        Time1->setAlignment(Qt::AlignCenter);
        label = new QLabel(groupBox_3);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 30, 71, 16));
        label->setAlignment(Qt::AlignCenter);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(530, 210, 201, 311));
        listWidget = new QListWidget(groupBox);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(10, 30, 181, 261));
        listWidget->setAutoScroll(true);
        listWidget->setFlow(QListView::TopToBottom);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 741, 25));
        menuBar->setDefaultUp(true);
        menuPlik = new QMenu(menuBar);
        menuPlik->setObjectName(QString::fromUtf8("menuPlik"));
        menuEdycja = new QMenu(menuBar);
        menuEdycja->setObjectName(QString::fromUtf8("menuEdycja"));
        menuPomoc = new QMenu(menuBar);
        menuPomoc->setObjectName(QString::fromUtf8("menuPomoc"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuPlik->menuAction());
        menuBar->addAction(menuEdycja->menuAction());
        menuBar->addAction(menuPomoc->menuAction());
        menuPlik->addAction(actionNowa_gra);
        menuPlik->addAction(actionWyjd);
        menuEdycja->addAction(actionCofnij);
        menuPomoc->addAction(actionO_programie);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "QChess", 0, QApplication::UnicodeUTF8));
        actionWyjd->setText(QApplication::translate("MainWindow", "Zako\305\204cz", 0, QApplication::UnicodeUTF8));
        actionWyjd->setShortcut(QApplication::translate("MainWindow", "Esc", 0, QApplication::UnicodeUTF8));
        actionNowa_gra->setText(QApplication::translate("MainWindow", "Nowa gra", 0, QApplication::UnicodeUTF8));
        actionCofnij->setText(QApplication::translate("MainWindow", "Cofnij", 0, QApplication::UnicodeUTF8));
        actionO_programie->setText(QApplication::translate("MainWindow", "O programie...", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Aktualny gracz", 0, QApplication::UnicodeUTF8));
        curPlayer->setText(QApplication::translate("MainWindow", "Brak", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Czasy", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Czarny", 0, QApplication::UnicodeUTF8));
        Time0->setText(QApplication::translate("MainWindow", "--:--", 0, QApplication::UnicodeUTF8));
        Time1->setText(QApplication::translate("MainWindow", "--:--", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Bia\305\202y", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", "Historia ruch\303\263w", 0, QApplication::UnicodeUTF8));
        menuPlik->setTitle(QApplication::translate("MainWindow", "Gra", 0, QApplication::UnicodeUTF8));
        menuEdycja->setTitle(QApplication::translate("MainWindow", "Edycja", 0, QApplication::UnicodeUTF8));
        menuPomoc->setTitle(QApplication::translate("MainWindow", "Pomoc", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
