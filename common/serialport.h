#ifndef SERIALPORT_H
#define SERIALPORT_H
#include <QObject>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>

class SerialPort : public QObject
{
    Q_OBJECT
public:
    explicit SerialPort(QObject *parent = nullptr);
    ~SerialPort();

public slots:
    QStringList availablePorts();
    int openPort(const QString &portName, qint32 baudRate);
    void closePort();
    void sendData(const QString &data);

signals:
    void dataReceived(const QString &data);
    void portOpened();
    void portClosed();

private slots:
    void readData();

private:
    QSerialPort m_serialPort;
};

#endif // SERIALPORT_H
