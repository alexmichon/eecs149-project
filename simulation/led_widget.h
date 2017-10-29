#ifndef LED_WIDGET_H
#define LED_WIDGET_H

#include <QWidget>

class LedWidget: public QWidget {

    Q_OBJECT

public:
    LedWidget(QWidget *parent = 0);
    void setState(bool state);
    void toggle();
    void setOnColor(QColor color);
    void setOffColor(QColor color);
    void setOnPattern(Qt::BrushStyle onPattern);
    void setOffPattern(Qt::BrushStyle offPattern);
    void setLedSize(int size);

public slots:
    void switchLedWidget();

protected:
    void paintEvent(QPaintEvent *);

private:
    bool lit;
    QColor ledOnColor;
    QColor ledOffColor;
    Qt::BrushStyle ledOnPattern;
    Qt::BrushStyle ledOffPattern;
    int ledSize;
};

#endif // LED_WIDGET_H

