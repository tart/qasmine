/****************************************************************************
 ** Qasmine : Command line tool to run jasmine specs
 **
 ** License : This application licensed under terms of LGPL
 ** You can check LICENSE file in this package
 **
 ** Contact : Osman Yüksel <yuxel@sonsuzdongu.com>
 **
 ** Howto use : ./qasmine /path/to/SpecRunner.html --verbose
 **
 ****************************************************************************/


#include <QtGui/QApplication>
#include "qasmine.h"
#include <iostream>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    Qasmine qasmine;

    //get arguments
    QString fileName = QString::fromLocal8Bit(argv[1]);
    QString verboseString = QString::fromLocal8Bit(argv[2]);

    if (qasmine.setFileName(fileName)) {
        qasmine.setVerbose(verboseString == "--verbose");
        qasmine.run();
        return a.exec();
    }

    return -1;
}
