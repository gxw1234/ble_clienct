#include "logwindow.h"
#include <QObject>
#include <QDateTime>
#include <QApplication>
#include <QDesktopWidget>
LogWindow::LogWindow(QWidget *parent) : QDialog(parent) {
    setWindowTitle("log");
//    setWindowFlags(windowFlags()| Qt::SubWindow | Qt::WindowCloseButtonHint| Qt::WindowStaysOnTopHint);
    setWindowFlags(windowFlags() | Qt::WindowCloseButtonHint);
    setStyleSheet("QDialog { background-color: #f0f0f0; }"
                  "QTextEdit { font-family: Arial; font-size: 12px; background-color: #ffffff;"
                  "border: 1px solid #cccccc; border-radius: 5px; padding: 5px; }");
    this->resize(1000,200);
    int screenHeight = QApplication::desktop()->screenGeometry().height();
    int windowHeight = this->height();
    int x = 0;
    int y = screenHeight - windowHeight;
    this->move(x,y);
    logWidget = new QTextEdit(this);
    logWidget->setReadOnly(true);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(logWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

}

LogWindow::~LogWindow() {
    delete logWidget;
}

void LogWindow::appendLog(const QString &log) {
    QDateTime currentTime = QDateTime::currentDateTime();
    QString formattedTime = currentTime.toString("yyyy-MM-dd HH:mm:ss");
    formattedTime += ":    ";
    logWidget->append( formattedTime + log);
}

void LogWindow::cleanLog()
{

    logWidget->clear();

}
