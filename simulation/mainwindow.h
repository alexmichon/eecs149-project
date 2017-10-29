#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "led_grid_layout.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void timerSlot();

private:
    Ui::MainWindow *ui;
    LedGridLayout * gridLayout;
    QTimer *timer;
};

#endif // MAINWINDOW_H
