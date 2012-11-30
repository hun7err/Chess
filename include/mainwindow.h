#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    QWidget *boardwid;
    void playerChange(const QString &q);
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_actionWyjd_triggered();
    void setCurrentPlayer(const QString &q);

    void on_actionNowa_gra_triggered();

signals:
    void setCurPlayer(const QString&);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
