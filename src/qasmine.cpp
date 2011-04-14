#include "qasmine.h"
#include <iostream>
#include <QtGui/QApplication>
#include <QDebug>
#include <QWebFrame>
#include <QVariant>

Qasmine::Qasmine() :
    QObject() 
{
    qDebug("inited");
    webView = new QWebView();
    connect(webView, SIGNAL(loadFinished(bool)), this, SLOT(finishLoading(bool)));
}

void Qasmine::run(QString file) 
{
    qDebug("file loaded");
    qDebug() << file;

    webView->load(file);
    
}

void Qasmine::finishLoading(bool isFinished) 
{
    qDebug("is finished");
    qDebug() << isFinished;

    QWebFrame *frame  = webView->page()->mainFrame();

    QVariant f1result = frame->evaluateJavaScript("return 'hede'");

    qDebug() << f1result.toString();






}
