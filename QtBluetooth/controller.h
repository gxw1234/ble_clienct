#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QLowEnergyController>
#include <QBluetoothDeviceInfo>
#include <QBluetoothLocalDevice>

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    void ConnectDevice(QBluetoothDeviceInfo info);
    void DisconnectDevice(void);
    QLowEnergyService *CreateService(QBluetoothUuid);

private:
    void SendMessage(QString);



private slots:
    void onConnected();
    void onDisconnected();
    void onStateChanged(QLowEnergyController::ControllerState state);
    void onError(QLowEnergyController::Error newError);

    void onServiceDiscovered(QBluetoothUuid);
    void onDiscoveryFinished();
    void onConnectionUpdated(const QLowEnergyConnectionParameters &parameters);
    void pairingFinished(const QBluetoothAddress &address, QBluetoothLocalDevice::Pairing pairing);
signals:
    void message(QString msg);
    void connect_State(QString State);
    void connect_err_info(QString State);
    void pair_end(bool result);
    void service_uuid_end(bool result);
    void serviceDiscovered(const QBluetoothUuid &newService);

private:
    QLowEnergyController *m_controller;
    QBluetoothLocalDevice *localDevice;
    QBluetoothAddress targetAddress;
};

#endif // CONTROLLER_H
