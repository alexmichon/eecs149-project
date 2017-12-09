#ifndef ARDUINO_SERIAL_READER_H
#define ARDUINO_SERIAL_READER_H

#include <QSerialPort>

#include "music_led_converter.h"

class ArduinoSerial: public QObject {
    Q_OBJECT

public:
    ArduinoSerial(const QString port, qint32 baudrate, MusicLedConverter *converter);
    ~ArduinoSerial();

    void start();
    void stop();

public slots:
    void onRead(const char *read);
    void handleReadyRead();

private:
    QSerialPort *mSerialPort;
    MusicLedConverter *mMusicLedConverter;

    bool mStarted;
};

#endif // ARDUINO_SERIAL_READER_H
