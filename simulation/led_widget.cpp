#include "led_widget.h"
#include <QPainter>

LedWidget::LedWidget(QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(28,28);
    lit = false;
    ledOnColor = Qt::black;
    ledOffColor = Qt::black;
    ledOnPattern = Qt::SolidPattern;
    ledOffPattern = Qt::SolidPattern;
    ledSize = 20;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(repaint()));
    timer->start(10);
}

void LedWidget::paintEvent(QPaintEvent *) {
    mutex.lock();
    QPainter p(this);
    lit ? p.setBrush(QBrush(ledOnColor, ledOnPattern)) : p.setBrush(QBrush(ledOffColor, ledOffPattern));
    p.drawEllipse(0,0,ledSize,ledSize);
    mutex.unlock();
}

void LedWidget::switchLedWidget() {
    mutex.lock();
    lit = !lit;
    mutex.unlock();
}

void LedWidget::setState(bool state) {
    mutex.lock();
    lit = state;
    mutex.unlock();
}

void LedWidget::toggle() {
    mutex.lock();
    lit = !lit;
    mutex.unlock();
}

void LedWidget::setOnColor(QColor onColor) {
    mutex.lock();
    ledOnColor = onColor;
    mutex.unlock();
}

void LedWidget::setOffColor(QColor offColor) {
    mutex.lock();
    ledOffColor = offColor;
    mutex.unlock();
}

void LedWidget::setOnPattern(Qt::BrushStyle onPattern) {
    mutex.lock();
    ledOnPattern = onPattern;
    mutex.unlock();
}

void LedWidget::setOffPattern(Qt::BrushStyle offPattern) {
    mutex.lock();
    ledOffPattern = offPattern;
    mutex.unlock();
}

void LedWidget::setLedSize(int size) {
    mutex.lock();
    ledSize = size;
    setFixedSize(size + 10, size + 10);
    mutex.unlock();
}
