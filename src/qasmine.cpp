/*****************************************************************************
 ** Qasmine : Command line tool to run jasmine specs
 **
 ** License : This application licensed under terms of Apache 2.0 License
 ** You can check LICENSE file in this package
 **
 ** Contact : Osman Yüksel <yuxel@sonsuzdongu.com>
 **
 ****************************************************************************/

#include "qasmine.h"
#include <iostream>
#include <QtGui/QApplication>
//#include <QDebug>
#include <QWebFrame>
#include <QFile>


Qasmine::Qasmine() :
    QObject() 
{
    webView = new QWebView();

    //initial values
    fileName = "";
    verbose = false;
}


/**
  * Set html fileName which contains SpecRunner
  */
bool Qasmine::setFileName(QString fileName) {

    QFile fileToOpen;
    fileToOpen.setFileName(fileName);

    if (!fileToOpen.exists()) {
        this->log("ERROR : File '" + fileName + "' does not exists");
        return false;
    }
    else {
        this->fileName = fileName;
        return true;
    }
}

/**
  * Set verbose mode true or false
  */
void Qasmine::setVerbose(bool isVerbose) {
    verbose = isVerbose;
}

/**
  * Load page, then execute specs
  */
void Qasmine::run()
{
    connect(webView, SIGNAL(loadFinished(bool)), this, SLOT(finishLoading(bool)));
    webView->load(fileName);
}


/**
  * Exit application by condition
  * This method will be called from JavaScript
  */
void Qasmine::exitConditionally(int errorCount){
    QApplication::instance()->exit(errorCount);
}


/**
  * Log method which will be run from JavaScript
  */
void Qasmine::log(const QString &text){
    //qDebug() << text;
    std::cout << text.toAscii().data() << "\n";
}

/**
  * Get qasmine.js which has its own Reporter
  */
QString Qasmine::getQasmineJs() {
    QString qasmineJs;
    QFile file;
    file.setFileName(":/qasmine.js");
    file.open(QIODevice::ReadOnly);
    qasmineJs = file.readAll();
    file.close();

    return qasmineJs;
}

/**
  * Prepere the execute command
  */
QString Qasmine::getQasmineJsCommand() {

    QString executeJasmineCmd = "var qasmineReporter = new jasmine.QasmineReporter();";

    if (verbose == true) {
        executeJasmineCmd        += "qasmineReporter.setVerbose(true);";
    }
    else {
        executeJasmineCmd        += "qasmineReporter.setVerbose(false);";
    }

    executeJasmineCmd        += "jasmine.getEnv().addReporter(qasmineReporter);";
    executeJasmineCmd        += "jasmine.getEnv().execute();";

    return executeJasmineCmd;
}

/**
  * When file finished, execute JavaScript functions
  */
void Qasmine::finishLoading(bool isFinished) 
{

    if (!isFinished) {
        this->log("ERROR: cannot load file : '" + fileName + "'");
        QApplication::instance()->exit(-1);
    }

    QWebFrame *frame  = webView->page()->mainFrame();

    frame->evaluateJavaScript(getQasmineJs());
    frame->addToJavaScriptWindowObject(QString("qasmine"), this);
    frame->evaluateJavaScript(getQasmineJsCommand());
}
