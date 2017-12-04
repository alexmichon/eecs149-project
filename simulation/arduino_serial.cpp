#include "arduino_serial.h"

ArduinoSerial::ArduinoSerial(char *port, int baudrate, MusicLedConverter *converter) {
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
    qDebug("Reading");
    QByteArray bytes = mSerialPort->readLine();
    onRead(QString::fromAscii(bytes.data()).toStdString().c_str());
}

ArduinoSerial::~ArduinoSerial() {
    mSerialPort->close();
}

void ArduinoSerial::onRead(const char *read) {
    int bin;
    int ampl;

    char *pch;

    pch = strtok((char*) read, "\t");
    if (pch == NULL) {
        return;
    }

    bin = atoi(pch);

    pch = strtok(NULL, "\t");
    if (pch == NULL) {
        return;
    }

    ampl = atoi(pch);

    qDebug("Bin: %d\tAmplitude: %d", bin, ampl);

    if (mMusicLedConverter != NULL) {
        mMusicLedConverter->convert(bin, ampl);
    }
}
