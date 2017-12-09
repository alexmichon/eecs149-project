#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H

#include <qmainwindow.h>
#include <qpushbutton.h>
#include "signal_generator.h"

#include "arduino_serial.h"
#include "music_led_converter.h"

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
    void handleLeftButton();
    void handleRightButton();
    void handleBrakeButton();
    void handleStopButton();

private:
    Ui::MainWindow *ui;
    LedGridLayout * gridLayout;

    QPushButton *leftButton;
    QPushButton *rightButton;
    QPushButton *brakeButton;
    QPushButton *stopButton;

    SignalGenerator *signalGenerator;
};

#endif // MAINWINDOW2_H
