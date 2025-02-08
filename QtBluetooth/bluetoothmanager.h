#ifndef BLUETOOTHMANAGER_H
#define BLUETOOTHMANAGER_H

#include <QObject>
class bluetoothmanager : public QObject
{
    Q_OBJECT
public:
    explicit bluetoothmanager(QObject *parent = nullptr);
    void remove_pari_name();
    void remove_pari_name_one();
private:
    void SendMessage(QString);

signals:
    void message(QString msg);
};

#endif // BLUETOOTHMANAGER_H
