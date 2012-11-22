/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Fri Nov 23 00:17:53 2012
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
    QWidget *centralWidget;
    QGroupBox *groupBox_2;
    QGroupBox *groupBox_3;
    QMenuBar *menuBar;
    QMenu *menuPlik;
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
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(530, 10, 201, 80));
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(530, 100, 201, 419));
        groupBox_3->setFlat(false);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 741, 25));
        menuBar->setDefaultUp(true);
        menuPlik = new QMenu(menuBar);
        menuPlik->setObjectName(QString::fromUtf8("menuPlik"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuPlik->menuAction());
        menuPlik->addAction(actionWyjd);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "QChess", 0, QApplication::UnicodeUTF8));
        actionWyjd->setText(QApplication::translate("MainWindow", "Wyjd\305\272", 0, QApplication::UnicodeUTF8));
        actionWyjd->setShortcut(QApplication::translate("MainWindow", "Esc", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Czas", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Statystyki", 0, QApplication::UnicodeUTF8));
        menuPlik->setTitle(QApplication::translate("MainWindow", "Plik", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
