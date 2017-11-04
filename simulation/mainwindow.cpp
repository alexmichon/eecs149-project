#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qmath.h>

#include "audio_thread.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ledStrip = new LedStripWidget(5, this);

    QWidget *w = new QWidget(this);
    QVBoxLayout *vlayout = new QVBoxLayout(w);
    w->setLayout(vlayout);

    QWidget *w1 = new QWidget(w);
    gridLayout = new LedGridLayout(w1);
    w1->setLayout(gridLayout);
    vlayout->addWidget(w1);

    startButton = new QPushButton("Start", w);
    startButton->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    vlayout->addWidget(startButton, 1);

    connect(startButton, SIGNAL (released()), this, SLOT (handleStartButton()));

    stopButton = new QPushButton("Stop", w);
    stopButton->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    vlayout->addWidget(stopButton, 1);

    connect(stopButton, SIGNAL (released()), this, SLOT (handleStopButton()));

    setCentralWidget(w);

    /*timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    timer->start(100);*/

    for (int i = 0; i < gridLayout->getStripCount(); i++) {
        LedStripLayout * stripLayout = gridLayout->getStrip(i);
        for (int j = 0; j < stripLayout->getLedCount(); j++) {
            stripLayout->getLed(j)->setState(true);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

QColor getColor(int i, int j) {
    static int counter = 0;
    int r = qCeil(255*qPow(qCos(counter), 2));
    int g = qCeil(255*qPow(qCos(counter + 90), 2));
    int b = qCeil(255*qPow(qCos(counter/2), 2));
    counter++;
    return QColor(r, g, b);
}

void MainWindow::timerSlot() {
    for (int i = 0; i < gridLayout->getStripCount(); i++) {
        LedStripLayout * stripLayout = gridLayout->getStrip(i);
        for (int j = 0; j < stripLayout->getLedCount(); j++) {
            QColor color = getColor(i, j);
            stripLayout->getLed(j)->setOnColor(color);
        }
    }
}



void MainWindow::handleStartButton() {
    audioThread = new AudioThread(gridLayout, "/home/alex/Berkeley/EECS149-Project/test/test3.mp3");
    //connect(audioThread, SIGNAL(newGridColors(RGB*, int, int)), gridLayout, SLOT(setColors(RGB*, int, int)));
    audioThread->start();
}

void MainWindow::handleStopButton() {
    audioThread->cancel();
}
