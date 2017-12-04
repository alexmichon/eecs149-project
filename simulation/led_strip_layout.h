#ifndef LED_STRIP_LAYOUT_H
#define LED_STRIP_LAYOUT_H

#include <QGridLayout>
#include <QWidget>
#include "led_widget.h"
#include "music_led_converter.h"

#define DEFAULT_NB_LEDS 10

class LedStripLayout : public QVBoxLayout
{
    Q_OBJECT
public:
    explicit LedStripLayout(QWidget *parent = 0, int nLeds = DEFAULT_NB_LEDS);

    int getLedCount();
    LedWidget * getLed(int column);

    void refresh();
    void enable(bool enabled);

    void setAmplitude(int amplitude, RGB color);

signals:

public slots:

private:
    int _nLeds;

};

#endif // LED_STRIP_LAYOUT_H
