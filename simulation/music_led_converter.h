#ifndef MUSIC_LED_CONVERTER_H
#define MUSIC_LED_CONVERTER_H

#include <QObject>

typedef struct {
    int r;
    int g;
    int b;
} RGB;

class MusicLedConverter : public QObject {
    Q_OBJECT
public:
    MusicLedConverter();

public slots:
    void convert(int bin, int *amplitude);

signals:
    void newValue(int strip, int amplitude, RGB color);

private:

    int mMaxAmplitude;

};

#endif // MUSIC_LED_CONVERTER_H
