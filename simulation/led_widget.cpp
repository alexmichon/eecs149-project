#include "led_widget.h"
#include <QPainter>

LedWidget::LedWidget(QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(28,28);
    lit = false;
    ledOnColor = Qt::red;
    ledOffColor = Qt::black;
    ledOnPattern = Qt::SolidPattern;
    ledOffPattern = Qt::SolidPattern;
    ledSize = 20;
}

void LedWidget::paintEvent(QPaintEvent *) {
    QPainter p(this);
    lit ? p.setBrush(QBrush(ledOnColor, ledOnPattern)) : p.setBrush(QBrush(ledOffColor, ledOffPattern));
    p.drawEllipse(0,0,ledSize,ledSize);
}

void LedWidget::switchLedWidget() {
    lit = !lit;
    repaint();
}

void LedWidget::setState(bool state) {
    lit = state;
    repaint();
}

void LedWidget::toggle() {
    lit = !lit;
    repaint();
}

void LedWidget::setOnColor(QColor onColor) {
    ledOnColor = onColor;
    repaint();
}

void LedWidget::setOffColor(QColor offColor) {
    ledOffColor = offColor;
    repaint();
}

void LedWidget::setOnPattern(Qt::BrushStyle onPattern) {
    ledOnPattern = onPattern;
    repaint();
}

void LedWidget::setOffPattern(Qt::BrushStyle offPattern) {
    ledOffPattern = offPattern;
    repaint();
}

void LedWidget::setLedSize(int size) {
    ledSize = size;
    setFixedSize(size + 10, size + 10);
    repaint();
}
