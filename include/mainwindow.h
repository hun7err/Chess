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
    void addHistory(const QString &q);
    explicit MainWindow(QWidget *parent = 0);
    void stopTimer();
    void startTimer(int interval);
    bool timerActive();
    void undoMove();
    ~MainWindow();
    
private slots:
    void on_actionWyjd_triggered();
    void setCurrentPlayer(const QString &q);
    void addHistoryItem(const QString &q);
    void on_actionNowa_gra_triggered();
    //void on_pushButton_clicked();
    void updateCaption();

    void on_actionCofnij_triggered();

    void on_actionO_programie_triggered();

signals:
    void setCurPlayer(const QString&);
    void addHistItem(const QString&);

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    int cur_player;
};

#endif // MAINWINDOW_H
