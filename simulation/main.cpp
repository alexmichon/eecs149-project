#include "mainwindow.h"
#include <QApplication>
//#include "my_audioinput.h"
#include "arduino_serial.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //ArduinoSerial *ARDUINO = new ArduinoSerial("/dev/ttyACM0", 115200);
    //ARDUINO->start();

    return a.exec();
}
