#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H

#include <qmainwindow.h>
#include <qpushbutton.h>
#include "signal_generator.h"

namespace Ui {
class MainWindow2;
}

class MainWindow2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow2(QWidget *parent = 0);
    ~MainWindow2();


public slots:
    void handleLeftButton();
    void handleRightButton();
    void handleBrakeButton();
    void handleStopButton();

private:
    Ui::MainWindow2 *ui;
    LedGridLayout * gridLayout;

    QPushButton *leftButton;
    QPushButton *rightButton;
    QPushButton *brakeButton;
    QPushButton *stopButton;

    SignalGenerator *signalGenerator;
};

#endif // MAINWINDOW2_H
