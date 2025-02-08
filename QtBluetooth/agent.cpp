#include "agent.h"
#include <QDebug>
Agent::Agent(QObject *parent) : QObject(parent)
{

    m_agent = new QBluetoothDeviceDiscoveryAgent(this);
    if(m_agent)
    {
        connect(m_agent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SLOT(onDeviceDiscovered(QBluetoothDeviceInfo)));
        connect(m_agent, SIGNAL(error(QBluetoothDeviceDiscoveryAgent::Error)), this, SLOT(onError(QBluetoothDeviceDiscoveryAgent::Error)));
        connect(m_agent, SIGNAL(finished()), this, SLOT(onFinished()));
        connect(m_agent, SIGNAL(canceled()), this, SLOT(onCanceled()));
    }
}

void Agent::startScanDevice(uint32_t timeOut, QString targetMacAddress)
{

    if(m_agent)
    {
        m_targetMacAddress = targetMacAddress;
        scan_flag =  false;
        m_agent->setLowEnergyDiscoveryTimeout(timeOut);
        m_agent->start();
        if(m_agent->isActive())
        {
            SendMessage("scanning...");
        }
    }
}




void Agent::SendMessage(QString msg)
{
    emit message(msg);
}

void Agent::ble_scan_start()
{
    m_agent->start();
}

void Agent::onDeviceDiscovered(const QBluetoothDeviceInfo &info)
{

    int rssi = info.rssi();
    QString rssiStr = "信号强度: " + QString::number(rssi);
    emit deviceDiscovered(info);
    QString tmp = "发现设备:";
    QString str = info.address().toString() + " - " + info.name()  + rssiStr;
    SendMessage(tmp + str);

    if (info.address().toString() == m_targetMacAddress)
    {
        scan_flag =true;
        m_agent->stop();

    }
}

void Agent::onError(QBluetoothDeviceDiscoveryAgent::Error err)
{
    QString str;

    str = QString("Agent Error(%1):").arg(err);
    str += m_agent->errorString();

    SendMessage(str);
}

void Agent::onFinished()
{
    SendMessage("Agent scan finished");
    emit Scan_end(scan_flag);
}

void Agent::onCanceled()
{
    emit Scan_end(scan_flag);
    SendMessage("Agent scan canceled...");
}
