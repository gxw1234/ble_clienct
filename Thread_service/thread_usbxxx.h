#ifndef THREAD_USBXXX_H
#define THREAD_USBXXX_H

//#include "usbxxx_arrange.h"
#include "usb/usbxxx_arrange.h"
#include <QThread>
#include <QDebug>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QObject>
class Thread_usbxxx:  public QObject
{
    Q_OBJECT
public:
    Thread_usbxxx();
    void scan_start();
    void init();
signals:
    void mySignal(int intValue, const QString &stringValue);
    void message();
public slots:
    void start();
//protected:
//    void run() override;

private slots:
    void onDeviceDiscovered(const QBluetoothDeviceInfo &info);
    void onError(QBluetoothDeviceDiscoveryAgent::Error err);
    void onFinished(void);
    void onCanceled(void);
private:
    void SendMessage();

    QBluetoothDeviceDiscoveryAgent *m_agent;

};

#endif // THREAD_USBXXX_H
