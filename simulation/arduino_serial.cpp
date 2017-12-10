#include "arduino_serial.h"

ArduinoSerial::ArduinoSerial(const QString port, qint32 baudrate, MusicLedConverter *converter) {
    mSerialPort = new QSerialPort();
    mSerialPort->setPortName(port);
    mSerialPort->setBaudRate(baudrate);
    mSerialPort->open(QIODevice::ReadWrite);

    mMusicLedConverter = converter;
}

void ArduinoSerial::start() {
    connect(mSerialPort, SIGNAL(readyRead()), this, SLOT(handleReadyRead()));
}

void ArduinoSerial::stop() {
    disconnect(mSerialPort, SIGNAL(readyRead()), this, SLOT(handleReadyRead()));
}

void ArduinoSerial::handleReadyRead() {
    QByteArray bytes = mSerialPort->readLine();
    onRead(QString::fromLocal8Bit(bytes.data()).toStdString().c_str());
}

ArduinoSerial::~ArduinoSerial() {
    mSerialPort->close();
}

void ArduinoSerial::onRead(const char *read) {
    int bin = 0;
    int ampl[10];

    char *pch;
    char *tmp;

    pch = strtok((char*) read, "\t");
    if (pch == NULL) {
        return;
    }

    while(pch != NULL) {
        ampl[bin] = strtol(pch, &tmp, 10);
        if (*tmp != '\0') { break; }

        bin++;
        pch = strtok(NULL, "\t");
    }

    emit(amplitudeRead(bin, ampl));
}
