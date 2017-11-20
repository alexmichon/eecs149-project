#include "mainwindow2.h"
#include <QApplication>
//#include "my_audioinput.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow2 w;
    w.show();

    //InputTest input;
    //input.show();

    return a.exec();
}
