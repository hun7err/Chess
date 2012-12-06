#include "timeset.h"
#include "ui_timeset.h"
#include <QObject>

TimeSet::TimeSet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TimeSet)
{
    ui->setupUi(this);
    QObject::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

TimeSet::~TimeSet()
{
    delete ui;
}

const QString TimeSet::getTime() {
    return ui->timeEdit->text();
}
