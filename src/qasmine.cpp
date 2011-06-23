/*****************************************************************************
 ** Qasmine : Command line tool to run jasmine specs
 **
 ** License : This application licensed under terms of LGPL
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
    connect(webView, SIGNAL(loadStarted()), this, SLOT(loadStarted()));
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
  * Read file content
  */
QString Qasmine::readFileContent(QString fileName) {
    QString fileContent;
    QFile file;
    file.setFileName(fileName);
    file.open(QIODevice::ReadOnly);
    fileContent = file.readAll();
    file.close();

    return fileContent;
}



/**
  * Prepere the execute command
  */
QString Qasmine::getQasmineJsCommand() {

    QString executeJasmineCmd = "var qasmineReporter = new jasmine.QasmineReporter();";

    if (verbose == true) {
        executeJasmineCmd    += "qasmineReporter.setVerbose(true);";
    }
    else {
        executeJasmineCmd    += "qasmineReporter.setVerbose(false);";
    }

    executeJasmineCmd        += "qasmineReporter.setQasmine(qasmine);";
    executeJasmineCmd        += "jasmine.getEnv().addReporter(qasmineReporter);";
    executeJasmineCmd        += "jasmine.getEnv().executeQasmine();";

    return executeJasmineCmd;
}

/**
  * When file finished, execute JavaScript functions
  */
void Qasmine::finishLoading(bool isFinished) 
{
    if (!isFinished) {
        this->log("ERROR: cannot load file : '" + fileName + "'");
        exitConditionally(255);
    }

    QWebFrame *frame  = webView->page()->mainFrame();

    frame->evaluateJavaScript(readFileContent(":/qasmine.js"));
    frame->addToJavaScriptWindowObject(QString("qasmine"), this);
    frame->evaluateJavaScript(getQasmineJsCommand());
}


/**
  * Before load started, override jasmine
  */
void Qasmine::loadStarted()
{
    QWebFrame *frame  = webView->page()->mainFrame();

    frame->evaluateJavaScript(readFileContent(":/override-jasmine.js"));
}
