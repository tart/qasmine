/*****************************************************************************
 ** Qasmine : Command line tool to run jasmine specs
 **
 ** License : This application licensed under terms of LGPL
 ** You can check LICENSE file in this package
 **
 ** Contact : Osman Yüksel <yuxel@sonsuzdongu.com>
 **
 ****************************************************************************/


#ifndef QASMINE_H
#define QASMINE_H

#include <QDialog>
#include <QWebView>

class Qasmine : public QObject {
    Q_OBJECT
public:
    Qasmine();

    bool setFileName(QString file);
    void setVerbose(bool);
    void run();

    QWebView *webView;
    bool verbose;
    QString fileName;

public slots:
    void log(const QString &text);
    void exitConditionally(int errorCount);

protected slots:
    void finishLoading(bool); 

protected:


private:
    QString getQasmineJs();
    QString getQasmineJsCommand();

};

#endif // QASMINE_H
