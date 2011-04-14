#ifndef QASMINE_H
#define QASMINE_H

#include <QDialog>
#include <QWebView>

class Qasmine : public QObject {
    Q_OBJECT
public:
    Qasmine();
    void run(QString file);
    QWebView *webView;

protected slots:
    void finishLoading(bool); 

protected:


private:

};

#endif // QASMINE_H
