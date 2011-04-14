#include <QtGui/QApplication>
#include "qasmine.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    Qasmine qasmine;
    QString fileName = QString::fromLocal8Bit(argv[1]);

    qasmine.run(fileName);
    return a.exec();
}
