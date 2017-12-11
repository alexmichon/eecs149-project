#ifndef ARDUINO_SERIAL_READER_H
#define ARDUINO_SERIAL_READER_H

#include <QSerialPort>
#include <QColor>

class ArduinoSerial: public QObject {
    Q_OBJECT

public:
    ArduinoSerial(const QString port, qint32 baudrate);
    ~ArduinoSerial();

    void start();
    void stop();

public slots:
    void onRead(const char *read);
    void handleReadyRead();

signals:
    void newLine(const char *line);
    void colorRead(int, QColor *);

private:
    QSerialPort *mSerialPort;

    bool mStarted;
};

#endif // ARDUINO_SERIAL_READER_H
