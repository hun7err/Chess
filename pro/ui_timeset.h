/********************************************************************************
** Form generated from reading UI file 'timeset.ui'
**
** Created: Thu Dec 6 12:45:51 2012
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMESET_H
#define UI_TIMESET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QTimeEdit>

QT_BEGIN_NAMESPACE

class Ui_TimeSet
{
public:
    QTimeEdit *timeEdit;
    QDialogButtonBox *buttonBox;
    QLabel *label;

    void setupUi(QDialog *TimeSet)
    {
        if (TimeSet->objectName().isEmpty())
            TimeSet->setObjectName(QString::fromUtf8("TimeSet"));
        TimeSet->setEnabled(true);
        TimeSet->resize(193, 96);
        timeEdit = new QTimeEdit(TimeSet);
        timeEdit->setObjectName(QString::fromUtf8("timeEdit"));
        timeEdit->setGeometry(QRect(40, 30, 101, 22));
        buttonBox = new QDialogButtonBox(TimeSet);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(10, 60, 171, 31));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(TimeSet);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 71, 16));

        retranslateUi(TimeSet);

        QMetaObject::connectSlotsByName(TimeSet);
    } // setupUi

    void retranslateUi(QDialog *TimeSet)
    {
        TimeSet->setWindowTitle(QApplication::translate("TimeSet", "Nowa gra", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("TimeSet", "Czas partii:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TimeSet: public Ui_TimeSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMESET_H
