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
    QTimer *timer;
    void playerChange(const QString &q);
    void addHistory(const QString &q);
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_actionWyjd_triggered();
    void setCurrentPlayer(const QString &q);
    void addHistoryItem(const QString &q);
    void on_actionNowa_gra_triggered();
    void on_pushButton_clicked();
    void updateCaption();

signals:
    void setCurPlayer(const QString&);
    void addHistItem(const QString&);

private:
    Ui::MainWindow *ui;
    int cur_player;
};

#endif // MAINWINDOW_H
