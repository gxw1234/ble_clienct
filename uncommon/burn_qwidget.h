#ifndef BURN_QWIDGET_H
#define BURN_QWIDGET_H
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include "tcpserver/tcpapp.h"
#include <QTextEdit>
class burn_qwidget : public QWidget
{
     Q_OBJECT
public:
    explicit burn_qwidget(QWidget *parent = nullptr);
    void initView();
    void setnetworkserviceOBJECT(Tcpapp *tcpaap ,bool status);
    bool connection_state;

private:

    QLabel *burn_qlabel=nullptr;
    QLineEdit *burn_lindit=nullptr;
    QPushButton *burn_button=nullptr;
    QPushButton *start_burn_button=nullptr;
    QPushButton *info_mac_button=nullptr;
    Tcpapp *tcpaap = nullptr;
    QTextEdit *showlog=nullptr;
private slots:
    void selection_path();
    void onstart_burn();
    void oninfo_mac_button();
    void handleDataReceived(quint8 dataType, const QByteArray& buffer,bool islen_, bool ismd5_);
    void handleConnected_state(bool connected_state);
};

#endif // BURN_QWIDGET_H
