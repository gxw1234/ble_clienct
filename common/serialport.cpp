#include "serialport.h"
#include <QDebug>

SerialPort::SerialPort(QObject *parent) : QObject(parent)
{
    connect(&m_serialPort, &QSerialPort::readyRead, this, &SerialPort::readData);
}

SerialPort::~SerialPort()
{
    if (m_serialPort.isOpen())
        m_serialPort.close();
}

QStringList SerialPort::availablePorts()
{
    QStringList portList;
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &port : ports)
    {
        portList.append(port.portName());
    }
    return portList;
}

int SerialPort::openPort(const QString &portName, qint32 baudRate)
{
    m_serialPort.setPortName(portName);
    m_serialPort.setBaudRate(baudRate);

    if (m_serialPort.open(QIODevice::ReadOnly))
    {
        qDebug() << "pass to open serial port.";
    }
    else
    {
        qDebug() << "Failed to open serial port.";
    }
    return 0;
}

void SerialPort::closePort()
{
    if (m_serialPort.isOpen())
    {
        m_serialPort.close();
        emit portClosed();
    }
}

void SerialPort::sendData(const QString &data)
{
    if (m_serialPort.isOpen())
    {
        m_serialPort.write(data.toUtf8());
    }
}

void SerialPort::readData()
{
    QByteArray data = m_serialPort.readAll();
    emit dataReceived(QString(data));
}
