#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>

#include "led_grid_layout.h"
#include "../src/audio/audio.h"
#include "audio_thread.h"

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
    void handleStartButton();
    void handleStopButton();

signals:
    void newColors(int strip, RGB *leds, int len);

private:
    Ui::MainWindow *ui;
    LedGridLayout * gridLayout;
    QPushButton *startButton;
    QPushButton *stopButton;

    QTimer *timer;

    AudioThread *audioThread;
};

#endif // MAINWINDOW_H
