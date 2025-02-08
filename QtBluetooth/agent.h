#ifndef AGENT_H
#define AGENT_H

#include <QObject>
#include <QBluetoothDeviceDiscoveryAgent>

class Agent : public QObject
{
    Q_OBJECT
public:
    explicit Agent(QObject *parent = nullptr);
    void startScanDevice(uint32_t timeOut,QString targetMacAddress);
    void ble_scan_start();

private:
    void SendMessage(QString);


private slots:
    void onDeviceDiscovered(const QBluetoothDeviceInfo &info);
    void onError(QBluetoothDeviceDiscoveryAgent::Error err);
    void onFinished(void);
    void onCanceled(void);
signals:
    void deviceDiscovered(const QBluetoothDeviceInfo &info);
    void message(QString msg);
    void Scan_end(bool scan_flag_b);
private:
    QBluetoothDeviceDiscoveryAgent *m_agent;
    QString m_targetMacAddress;
    bool scan_flag;
};

#endif // AGENT_H
