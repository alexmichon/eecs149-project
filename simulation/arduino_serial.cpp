#include "arduino_serial.h"

ArduinoSerial::ArduinoSerial(const QString port, qint32 baudrate) {
    mSerialPort = new QSerialPort();
    mSerialPort->setPortName(port);
    mSerialPort->setBaudRate(baudrate);
    mSerialPort->open(QIODevice::ReadWrite);
    mSerialPort->flush();
}

void ArduinoSerial::start() {
    connect(mSerialPort, SIGNAL(readyRead()), this, SLOT(handleReadyRead()));
    connect(this, SIGNAL(newLine(const char*)), this, SLOT(onRead(const char*)));
}

void ArduinoSerial::stop() {
    disconnect(mSerialPort, SIGNAL(readyRead()), this, SLOT(handleReadyRead()));
}

void ArduinoSerial::handleReadyRead() {
    while(mSerialPort->canReadLine()) {
        QByteArray bytes = mSerialPort->readLine();
        emit(newLine(QString::fromLocal8Bit(bytes.data()).toStdString().c_str()));
    }
}

ArduinoSerial::~ArduinoSerial() {
    mSerialPort->close();
}

void ArduinoSerial::onRead(const char *read) {

    int index;
    quint32 color;
    quint8 r;
    quint8 g;
    quint8 b;

    char *pch;
    char *tmp;

    pch = strtok((char*) read, "\t");
    while(pch != NULL) {
        index = strtol(pch, &tmp, 10);
        if (tmp == pch) {
            break;
        }

        pch = strtok(NULL, "\t");
        if (pch == NULL) {
            break;
        }

        color = strtol(pch, &tmp, 10);
        if (tmp == pch) {
            break;
        }

        emit(colorRead(index, new QColor((color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF)));

        pch = strtok(NULL, "\t");
        if (pch == NULL) {
            break;
        }
    }
}
