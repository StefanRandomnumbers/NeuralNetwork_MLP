#include "mainwindow.h"
#include <QApplication>
#include <qdebug.h>
#include <random>
#include <cstdlib>
#include <ctime>
#include <cmath>


int main(int argc, char *argv[])
{
    srand(time(0));



    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("Stefan Fohs GmbH & Co. KG");
    QCoreApplication::setApplicationName("NeuralNet GUI");

    MainWindow w;
    w.setWindowTitle("NeuralNet GUI");

    w.show();

    return a.exec();
}
