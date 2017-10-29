#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qmath.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ledStrip = new LedStripWidget(5, this);

    QWidget *w = new QWidget(this);

    gridLayout = new LedGridLayout(w);
    w->setLayout(gridLayout);
    setCentralWidget(w);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    timer->start(100);

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
