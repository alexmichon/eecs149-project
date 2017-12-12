#include "mainwindow.h"
#include "ui_mainwindow2.h"

#include "left_generator.h"
#include "right_generator.h"
#include "brake_generator.h"

#include "arduino_serial.h"
#include "music_led_converter.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget *w = new QWidget(this);
    QVBoxLayout *vlayout = new QVBoxLayout(w);
    w->setLayout(vlayout);

    QWidget *w1 = new QWidget(w);
    gridLayout = new LedGridLayout(w1, 10, 10);
    w1->setLayout(gridLayout);
    vlayout->addWidget(w1);

    leftButton = new QPushButton("Left", w);
    leftButton->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    vlayout->addWidget(leftButton, 1);

    rightButton = new QPushButton("Right", w);
    rightButton->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    vlayout->addWidget(rightButton, 1);

    brakeButton = new QPushButton("Brake", w);
    brakeButton->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    vlayout->addWidget(brakeButton, 1);

    stopButton = new QPushButton("Stop", w);
    stopButton->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    vlayout->addWidget(stopButton, 1);

    setCentralWidget(w);

    connect(leftButton, SIGNAL (released()), this, SLOT (handleLeftButton()));
    connect(rightButton, SIGNAL (released()), this, SLOT (handleRightButton()));
    connect(brakeButton, SIGNAL (released()), this, SLOT (handleBrakeButton()));
    connect(stopButton, SIGNAL (released()), this, SLOT (handleStopButton()));

    ArduinoSerial *ARDUINO = new ArduinoSerial("COM11", 115200);
    ARDUINO->start();

    gridLayout->enable(true);

    connect(ARDUINO, SIGNAL(colorRead(int,QColor *)), gridLayout, SLOT(setColor(int,QColor *)));

    QTimer *timer = new QTimer(this);
    timer->setInterval(20);
    connect(timer, SIGNAL(timeout()), gridLayout, SLOT(refresh()));
}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::handleLeftButton() {
    if (signalGenerator != NULL) {
        signalGenerator->stop();
    }
    signalGenerator = new LeftGenerator(gridLayout);
    signalGenerator->start();
}

void MainWindow::handleRightButton() {
    if (signalGenerator != NULL) {
        signalGenerator->stop();
    }
    signalGenerator = new RightGenerator(gridLayout);
    signalGenerator->start();
}

void MainWindow::handleBrakeButton() {
    if (signalGenerator != NULL) {
        signalGenerator->stop();
    }
    signalGenerator = new BrakeGenerator(gridLayout);
    signalGenerator->start();
}

void MainWindow::handleStopButton() {
    if (signalGenerator != NULL) {
        signalGenerator->stop();
    }
}
