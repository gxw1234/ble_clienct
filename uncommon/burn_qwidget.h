#ifndef BURN_QWIDGET_H
#define BURN_QWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "tcpserver/tcpapp.h"
#include <QTextEdit>
#include <QThread>

// 声明ProcessThread类
class ProcessThread : public QThread
{
    Q_OBJECT
public:
    explicit ProcessThread(const QString& program, const QStringList& args, QObject* parent = nullptr);

signals:
    void outputReceived(const QString& text);
    void errorOccurred(const QString& error);

protected:
    void run() override;

private:
    QString m_program;
    QStringList m_args;
};

class burn_qwidget : public QWidget
{
    Q_OBJECT
public:
    explicit burn_qwidget(QWidget *parent = nullptr);
    void setnetworkserviceOBJECT(Tcpapp *m_tcpaap, bool status);

private slots:
    void selection_path();
    void onstart_burn();
    void oninfo_mac_button();
    void handleDataReceived(quint8 dataType, const QByteArray &buffer, bool islen_, bool ismd5_);
    void handleConnected_state(bool connected_state);

private:
    void initView();
    QLabel *burn_qlabel;
    QLineEdit *burn_lindit;
    QPushButton *burn_button;
    QPushButton *start_burn_button;
    QPushButton *info_mac_button;
    QTextEdit *showlog;
    Tcpapp *tcpaap = nullptr;
    bool connection_state = false;
};

#endif // BURN_QWIDGET_H
