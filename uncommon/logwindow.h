#ifndef LOGWINDOW_H
#define LOGWINDOW_H


#include <QDialog>
#include <QTextEdit>
#include <QVBoxLayout>

class LogWindow : public QDialog {
    Q_OBJECT
public:
    LogWindow(QWidget *parent = nullptr);
    ~LogWindow();

    void appendLog(const QString &log);
    void cleanLog();

private:
    QTextEdit *logWidget;
};

#endif // LOGWINDOW_H
