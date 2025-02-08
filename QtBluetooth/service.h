#ifndef SERVICE_H
#define SERVICE_H

#include <QObject>
#include <QLowEnergyService>

class Service : public QObject
{
    Q_OBJECT
public:
    explicit Service(QObject *parent = nullptr);

    void ConnectService(QLowEnergyService *);
    void SendMessage(QString);
    void OpenNotify(QLowEnergyCharacteristic ch, bool flag);
    void ReadCharacteristic(QLowEnergyCharacteristic ch);
    void WriteCharacteristic(QLowEnergyCharacteristic ch, QByteArray arr);

private slots:
    void onStateChanged(QLowEnergyService::ServiceState newState);
    void onCharacteristicChanged(const QLowEnergyCharacteristic &info,
                               const QByteArray &value);
    void onCharacteristicRead(const QLowEnergyCharacteristic &info,
                            const QByteArray &value);
    void onCharacteristicWritten(const QLowEnergyCharacteristic &info,
                               const QByteArray &value);
    void onDescriptorRead(const QLowEnergyDescriptor &info,
                        const QByteArray &value);
    void onDescriptorWritten(const QLowEnergyDescriptor &info,
                           const QByteArray &value);
    void onError(QLowEnergyService::ServiceError error);

signals:
    void onStateChanged_end();
    void discoveryCharacteristic(QLowEnergyCharacteristic);
    void message(QString);
    void onKeyresult(QString);
    void onaudio(QString);

private:
    QLowEnergyService * m_service;
    QMap<QString, QString> mapping;
    QString uuid1 = "{0000fc28-0000-1000-8000-00805f9b34fb}";
    QString uuid2 ="{0000fc26-0000-1000-8000-00805f9b34fb}";
    QString service_value = "0000000000000000000000000000000000000000";


};

#endif // SERVICE_H
